#include "HierarchicalConfiguration.hpp"

#include <algorithm>
#include <functional>

#include "coconut-tools/utils/pointee.hpp"

#include "../configuration-exceptions.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

std::shared_ptr<HierarchicalConfiguration> HierarchicalConfiguration::create(const std::string& text) {
    return Node(new HierarchicalConfiguration(text));
}

HierarchicalConfiguration::HierarchicalConfiguration(const HierarchicalConfiguration& other) :
    name_(other.name_),
    text_(other.text_) {
    std::transform(
            other.children_.begin(),
            other.children_.end(),
            std::back_inserter(children_),
            std::bind(&HierarchicalConfiguration::copy_, std::placeholders::_1)
            );
}

HierarchicalConfiguration& HierarchicalConfiguration::operator=(const HierarchicalConfiguration& other) {
    if (&other != this) {
        name_ = other.name_;
        text_ = other.text_;
        children_.clear();
        std::transform(
                other.children_.begin(),
                other.children_.end(),
                std::back_inserter(children_),
                std::bind(&HierarchicalConfiguration::copy_, std::placeholders::_1)
                );
    }

    return *this;
}

bool HierarchicalConfiguration::operator==(const HierarchicalConfiguration& other) const {
    // XXX: Not comparing name_ here, because of the way adding works. Is this ok?
    return text_ == other.text_ &&
            children_.size() == other.children_.size() &&
            std::equal(children_.begin(), children_.end(), other.children_.begin());
}

std::ostream& HierarchicalConfiguration::print(std::ostream& os) const {
    return print_(os, 0);
}

void HierarchicalConfiguration::clear() {
    children_.clear();
}

bool HierarchicalConfiguration::empty() const {
    if (!text_.empty()) {
        return false;
    } else {
        return children_.end() ==
                std::find_if(
                        children_.begin(),
                        children_.end(),
						[](const Node& node) { return !node->empty(); }
						);
    }
}

size_t HierarchicalConfiguration::count(const node::Path& key) const {
    Nodes nodes;
    find_(key, &nodes);
    return nodes.size();
}

HierarchicalConfiguration::Value HierarchicalConfiguration::get(
        const node::Path& key
        ) const {
    Nodes nodes;
    find_(key, &nodes);
    if (nodes.empty()) {
        throw MissingRequiredValue(key.string());
    } else if (nodes.size() > 1) {
        throw MultipleValuesWhereSingleValueRequired(key.string());
    } else {
        return nodes.front();
    }
}

void HierarchicalConfiguration::getAll(const node::Path& key, Nodes* valuesParam) const {
    Nodes& values = utils::pointee(valuesParam);
    find_(key, &values);
}

void HierarchicalConfiguration::set(const node::Path& key, ValueParam value) {
    node::Path parent = key.parentPath();
    Node parentNode = findSingle_(parent, parent);
    erase_(parentNode, key.child());
    add_(parentNode, key.child(), value);
}

void HierarchicalConfiguration::add(const node::Path& key, ValueParam value) {
    node::Path parent = key.parentPath();
    Node parentNode = findSingle_(parent, parent);
    add_(parentNode, key.child(), value);
}

void HierarchicalConfiguration::erase(const node::Path& key) {
    node::Path parent = key.parentPath();
    Node parentNode = findSingle_(parent, parent);
    erase_(parentNode, key.child());
}

void HierarchicalConfiguration::keys(Keys* keysParam) const {
    Keys& k = utils::pointee(keysParam);
    std::for_each(
            children_.begin(),
            children_.end(),
			[&k](Node node) { node->keys_(node::Specifier(), &k); }
            );
}

bool HierarchicalConfiguration::is(const std::string& name) const {
    return name_ == name;
}

HierarchicalConfiguration::HierarchicalConfiguration(
            const std::string& text,
            const std::string& name,
            const Nodes& children
            ) :
            name_(name),
            text_(text),
            children_(children) {
}

HierarchicalConfiguration::Node HierarchicalConfiguration::copy_() const {
    return Node(new HierarchicalConfiguration(*this));
}

void HierarchicalConfiguration::find_(
        const node::Path& key,
        Nodes* nodesParam
        ) const {
    Nodes& nodes = utils::pointee(nodesParam);

	if (key.selectorMatches(*this)) {
		if (!key.hasChildren()) {
			// XXX: Dirty! shared_from_this has a different const-correctness tactic
			// to shared_ptr, so we either have to reimplement it or use const_cast...
			nodes.push_back(const_cast<HierarchicalConfiguration&>(*this).shared_from_this());
		} else {
			std::string head = key.root();
			node::Path tail = key.childPath();

			Nodes::const_iterator it, end = children_.end();
			for (it = children_.begin(); it != end; ++it) {
				if ((*it)->name_ == head) {
					(*it)->find_(tail, &nodes);
				}
			}
		}
	}
}

HierarchicalConfiguration::Node HierarchicalConfiguration::findSingle_(
        const node::Path& key,
        const node::Path& originalKey
        ) const {
	if (!key.hasChildren()) {
		// XXX: Dirty! shared_from_this has a different const-correctness tactic
		// to shared_ptr, so we either have to reimplement it or use const_cast...
		return const_cast<HierarchicalConfiguration&>(*this).shared_from_this();
	} else {
		std::string head = key.root();
		node::Path tail = key.childPath();

		Node result;
		Nodes::const_iterator it, end = children_.end();
		for (it = children_.begin(); it != end; ++it) {
			if ((*it)->name_ == head) {
				if (!result) {
					result = (*it)->findSingle_(tail, originalKey);
				} else {
					throw MultipleValuesWhereSingleValueRequired(originalKey.string());
				}
			}
		}

		if (!result) {
			throw MissingRequiredValue(originalKey.string());
		} else {
			return result;
		}
	}
}

void HierarchicalConfiguration::add_(Node parent, const std::string& childName, ValueParam value) {
    Node child(new HierarchicalConfiguration(*value));
    child->name_ = childName;
    parent->children_.push_back(child);
}

void HierarchicalConfiguration::erase_(Node parent, const std::string& childName) {
    Nodes::iterator end = std::remove_if(
            parent->children_.begin(),
            parent->children_.end(),
            std::bind(&HierarchicalConfiguration::is, std::placeholders::_1, std::cref(childName))
            );
    parent->children_.erase(end, parent->children_.end());
}

void HierarchicalConfiguration::keys_(const node::Specifier& parent, Keys* keysParam) const {
    Keys& k = utils::pointee(keysParam);

    node::Specifier node = parent / name_;
    k.insert(node);

    std::for_each(
            children_.begin(),
            children_.end(),
            std::bind(&HierarchicalConfiguration::keys_, std::placeholders::_1, std::cref(node), &k)
    );
}

std::ostream& HierarchicalConfiguration::print_(std::ostream& os, size_t indentation) const {
    os << std::string(indentation, ' ');
    os << name_;
    if (!text_.empty()) {
        os << " = \"" << text_ << '\"';
    }
    os << '\n';
    std::for_each(
            children_.begin(),
            children_.end(),
            std::bind(&HierarchicalConfiguration::print_, std::placeholders::_1, std::ref(os), indentation +  1)
            );
    return os;
}
