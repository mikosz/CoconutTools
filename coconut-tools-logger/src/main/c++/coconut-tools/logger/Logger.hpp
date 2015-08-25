#ifndef COCONUTTOOLS_LOGGER_LOGGER_HPP_
#define COCONUTTOOLS_LOGGER_LOGGER_HPP_

#include <sstream>
#include <cassert>
#include <vector>
#include <functional>

#include <boost/call_traits.hpp>
#include <boost/noncopyable.hpp>

#include "coconut-tools/concurrent/Lockable.hpp"

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

#include "appender/Appender.hpp"
#include "Level.hpp"
#include "Context.hpp"
#include "print.hpp"

namespace coconut_tools {
namespace logger {

class Logger : public concurrent::Lockable<Logger> {
private:

    class Stream {
    public:

        template <class T>
        Stream& operator<< (const T& v) {
			print(oss_, v);
			return *this;
        }

        void flush() {
            assert(context_);

            std::for_each(
            		appenders_.begin(),
            		appenders_.end(),
            		std::bind(&appender::Appender::append, std::placeholders::_1, level_, *context_, oss_.str())
            );

            oss_.rdbuf()->str("");
        }

        void reset(Level level, const Context& context) {
        	level_ = level;
            context_ = &context;
        }

    private:

        friend class Logger;

        typedef std::vector<appender::AppenderSharedPtr> Appenders;

        Stream() :
        	level_(Level::INFO),
            context_(0) {
        }

        std::ostringstream oss_;

        Level level_;

        const Context* context_;

        Appenders appenders_;

    };

public:

    class StreamRef : boost::noncopyable {
    public:

        StreamRef() :
            stream_(0),
            loggerLock_(new WriteLock) {
        }

        StreamRef(Stream& stream, Level level, const Context& context) :
            stream_(&stream),
            loggerLock_(new WriteLock)
        {
            stream_->reset(level, context);
        }

		StreamRef(StreamRef&& other) :
			stream_(other.stream_),
			loggerLock_(other.loggerLock_)
		{
			other.stream_ = 0;
			other.loggerLock_.reset();
		}

        ~StreamRef() {
            if (stream_) {
                stream_->flush();
            }
        }

        template <class T>
        StreamRef& operator<< (const T& v) {
            if (stream_) {
                *stream_ << v;
            }
            return *this;
        }

        WriteLock& loggerLock() {
            return *loggerLock_;
        }

    private:

        Stream* stream_;

        std::shared_ptr<WriteLock> loggerLock_;

    };

    Logger(Level level) :
    	level_(level)
    {
    }

    StreamRef log(Level level, const Context& context = Context::DEFAULT) {
        if (level_ > level) {
            return StreamRef();
        } else {
            return StreamRef(stream_, level, context);
        }
    }

    StreamRef log(Level level, const Context& context = Context::DEFAULT) volatile {
        WriteLocked self = lock();
        StreamRef result = self->log(level, context);
        result.loggerLock().swap(self.lock());
        return result;
    }

    StreamRef trace(const Context& context = Context::DEFAULT) {
    	return log(Level::TRACE, context);
    }

    StreamRef trace(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::TRACE, context);
    }

    StreamRef debug(const Context& context = Context::DEFAULT) {
    	return log(Level::DEBUG, context);
    }

    StreamRef debug(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::DEBUG, context);
    }

    StreamRef info(const Context& context = Context::DEFAULT) {
    	return log(Level::INFO, context);
    }

    StreamRef info(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::INFO, context);
    }

    StreamRef warning(const Context& context = Context::DEFAULT) {
    	return log(Level::WARNING, context);
    }

    StreamRef warning(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::WARNING, context);
    }

    StreamRef error(const Context& context = Context::DEFAULT) {
    	return log(Level::ERROR, context);
    }

    StreamRef error(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::ERROR, context);
    }

    StreamRef critical(const Context& context = Context::DEFAULT) {
    	return log(Level::CRITICAL, context);
    }

    StreamRef critical(const Context& context = Context::DEFAULT) volatile {
    	return log(Level::CRITICAL, context);
    }

    void addAppender(appender::AppenderSharedPtr appender) {
    	stream_.appenders_.push_back(appender);
    }

    void addAppender(appender::AppenderSharedPtr appender) volatile {
    	lock()->addAppender(appender);
    }

    Level getLevel() const {
    	return level_;
    }

    Level getLevel() const volatile {
    	return lock()->getLevel();
    }

    void setLevel(Level level) {
    	level_ = level;
    }

    void setLevel(Level level) volatile {
    	lock()->setLevel(level);
    }

private:

    Level level_;

    Stream stream_;

	friend class concurrent::Lockable<Logger>;

};

CT_SMART_POINTER_DEFINITONS(Logger);

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_LOGGER_HPP_ */
