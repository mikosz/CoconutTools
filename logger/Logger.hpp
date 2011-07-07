#ifndef COCONUTTOOLS_LOGGER_LOGGER_HPP_
#define COCONUTTOOLS_LOGGER_LOGGER_HPP_

#include <sstream>
// tmp
#include <iostream>
#include <cassert>

#include <boost/call_traits.hpp>

#include "concurrent/Lockable.hpp"
#include "Level.hpp"
#include "Context.hpp"

namespace CoconutTools {
namespace logger {

class Logger : concurrent::Lockable<Logger> {
private:

    friend class concurrent::Lockable<Logger>;

    class Stream {
    public:

        template <class T>
        Stream& operator<< (const T& v) {
            oss_ << v;
            return *this;
        }

        void flush() {
            assert(context_);

            std::cerr << oss_.str() << '\n';
            oss_.rdbuf()->str("");
        }

        void reset(const Context& context) {
            context_ = &context;
        }

    private:

        Stream() :
            context_(0) {
        }

        std::ostringstream oss_;

        const Context* context_;

        friend class Logger;

    };

public:

    class StreamRef {
    public:

        StreamRef() :
            stream_(0),
            loggerLock_(new WriteLock) {
        }

        StreamRef(Stream& stream, const Context& context) :
            stream_(&stream),
            loggerLock_(new WriteLock) {
            stream_->reset(context);
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

        boost::shared_ptr<WriteLock> loggerLock_;

    };

    Logger(Level level) :
        level_(level) {
    }

    StreamRef log(const Context& context) {
        if (level_ > context.level) {
            return StreamRef();
        } else {
            return StreamRef(stream_, context);
        }
    }

    StreamRef log(const Context& context) volatile {
        WriteLockingPtr self = lock<WriteLock>();
        StreamRef result = self->log(context);
        result.loggerLock().swap(self.lock());
        return result;
    }

private:

    Level level_;

    Stream stream_;

};

}  // namespace logger
}  // namespace CoconutTools {

#endif /* COCONUTTOOLS_LOGGER_LOGGER_HPP_ */
