// asyncloop.h
//
// Copyright (c) 2012-2016, Paulo Caetano
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the
//      names of any other contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef ASYNCLOOP_H
#define ASYNCLOOP_H

#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace pt { namespace pcaetano { namespace bluesy {
namespace utils
{

enum TaskState { TASK_DONE, TASK_WORKING };

/*!
 * \brief AsyncLoopSocket Drives an asio loop based on socket activity.
 * \param doWork Functor that will get called when asio signals activity on the socket.
 *  It's responsible for signalling whether the task is over.
 * \param sock The socket.
 * \param isRead Indicates whether we're reading or writing.
 *
 * \todo doWork will become a template argument.
 * \todo Check if we can replace isRead with a functor for the correct socket's method (rear/write).
 */
void AsyncLoopSocket(boost::function<TaskState()> doWork, boost::asio::ip::tcp::socket& sock, bool isRead);

/*!
 * \brief AsyncLoopTimer Drives an asio loop based on a timer.
 * \param doWork Functor that will get called when the timer expires.
 *  It's responsible for signalling whether the task is over.
 * \param dTimer The timer.
 * \param millisecs Inteval for timer inactivity.
 *
 * \todo doWork will become a template argument.
 */
void AsyncLoopTimer(boost::function<TaskState()> doWork, boost::asio::deadline_timer& dTimer, int millisecs);

} // namespace utils
}}}

#endif // ASYNCLOOP_H
