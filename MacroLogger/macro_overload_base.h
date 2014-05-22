// Copyright (c) 2013-2014, Paulo Caetano
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of the copyright holder nor the names of any other
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MACRO_OVERLOAD_BASE_H
#define MACRO_OVERLOAD_BASE_H


// These macros allow iteration on the received arguments, applying an
// action on each argument. This is achieved by "overloading" based on
// the number of arguments, hence the name.

// I feel like I've been all over the web on this journey. While the places
// have been too numerous to mention, I believe I should note here the
// starting points:
// http://efesx.com/2010/07/17/variadic-macro-to-count-number-of-arguments/
// http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
// http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments

// At first, I tried to distinguish the 0-arguments case from the rest.
// However, I didn't manage a solution simple enough to my liking. So, in the
// end, I settled for distinguishing between 1 argument and the rest.
// A call with 0 arguments will be flagged as 1 argument, but when the compiler
// steps in, the error will be detected.

// While this sounded very promising, we have a problem here.
// sizeof() isn't evaluated on cpp, but on compilation.
// This means... (see next coment)
// #define VA_NUM_ARGS(...) VA_NUM_ARGS_2(__VA_ARGS__)
// #define VA_NUM_ARGS_2(...)
//    (sizeof(#__VA_ARGS__) == sizeof("")
//     ? 0 : VA_NUM_ARGS_IMPL_2(__VA_ARGS__, 5,4,3,2,1))
//#define VA_NUM_ARGS_IMPL_2(_1,_2,_3,_4,_5,N,...) N

// ... something like this will fail, because cpp won't concatenate
// XPTO_ with 0 (e.g.), but rather with the expression above, i.e.,
// (sizeof etc). In the end, this gives us an error, as we attempt
// to concatenate XPTO_ and (
// #define MYRUN_TEST(x, ...) MYRUN_TEST_2(x, VA_NUM_ARGS(__VA_ARGS__))
// #define MYRUN_TEST_2(x, N) MYRUN_TEST_3(x, N)
// #define MYRUN_TEST_3(x, N) XPTO_##N(x)
// #define XPTO_0(x) s.Debug((x))

// OTOH, this won't work, either, because both versions will make it to
// compilation, and one is obviously illegal:
// (sizeof("") == sizeof("") ? 0 : 1) > 0 ? s.Debug((string{"a"}) +()) : s.Debug((string{"a"}));
//
// #define MYRUN_TEST_1(x, ...)
//    VA_NUM_ARGS(__VA_ARGS__) > 0 ?
//    s.Debug((x) FOR_EACH(+, __VA_ARGS__)) :
//    s.Debug((x))

// List of macros to apply an action to a list of arguments
// Works only for a total of 16 arguments
#define PCBASE__MOVERLOAD_FE_1(ACTION, X) ACTION(X)
#define PCBASE__MOVERLOAD_FE_2(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_1(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_3(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_2(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_4(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_3(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_5(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_4(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_6(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_5(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_7(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_6(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_8(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_7(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_9(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_8(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_10(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_9(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_11(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_10(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_12(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_11(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_13(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_12(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_14(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_13(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_15(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_14(ACTION, __VA_ARGS__)
#define PCBASE__MOVERLOAD_FE_16(ACTION, X, ...) ACTION(X)PCBASE__MOVERLOAD_FE_15(ACTION, __VA_ARGS__)

// Selects a value based on the received arg list
// Works only for a total of 16 arguments
//
// The idea is that the caller's first arg is __VA_ARGS__. The rest of the
// caller's args should be a list of the values the caller wants, one value
// for each "amount" of args. E.g.,
//      VA_NUM_ARGS("a", 1, 2)
//          -> SELECT_VALUE("a", 1, 2, 16,15,14,13,12,11,9,8,7,6,5,4,3,2,1)
// This means _1 == "a" and, following the sequence, NAME == 3
// So, VA_NUM_ARGS("a", 1, 2) == 3, i.e., it has 3 arguments
#define PCBASE__MOVERLOAD_SELECT_VALUE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,NAME,...) NAME

// Apply an action to each argument on the list.
// E.g.:
//  << arg1 << arg2 << arg3
//  + arg1 + arg2 + arg3
// Works only for a total of 16 arguments
#define PCBASE__MOVERLOAD_FOR_EACH(action, ...) \
  PCBASE__MOVERLOAD_SELECT_VALUE(__VA_ARGS__,PCBASE__MOVERLOAD_FE_16,PCBASE__MOVERLOAD_FE_15,\
    PCBASE__MOVERLOAD_FE_14,PCBASE__MOVERLOAD_FE_13,PCBASE__MOVERLOAD_FE_12,PCBASE__MOVERLOAD_FE_11,\
    PCBASE__MOVERLOAD_FE_10,PCBASE__MOVERLOAD_FE_9,PCBASE__MOVERLOAD_FE_8,PCBASE__MOVERLOAD_FE_7,\
    PCBASE__MOVERLOAD_FE_6,PCBASE__MOVERLOAD_FE_5,PCBASE__MOVERLOAD_FE_4,PCBASE__MOVERLOAD_FE_3,\
    PCBASE__MOVERLOAD_FE_2,PCBASE__MOVERLOAD_FE_1)(action,__VA_ARGS__)

// When using a binary operator, we need to distinguish the case where
// we have only one argument from all the other cases
// Works only for a total of 16 arguments
#define PCBASE__MOVERLOAD_ONE_ARG_OR_MORE(...) \
    PCBASE__MOVERLOAD_SELECT_VALUE(__VA_ARGS__, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1)

// Counts the number of arguments received
// Works only for a total of 16 arguments
#define PCBASE__MOVERLOAD_VA_NUM_ARGS(...) \
    PCBASE__MOVERLOAD_SELECT_VALUE(__VA_ARGS__, 16,15,14,13,12,11,9,8,7,6,5,4,3,2,1)


#endif // MACRO_OVERLOAD_BASE_H
