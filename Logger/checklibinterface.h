#ifndef CHECKLIBINTERFACE_H
#define CHECKLIBINTERFACE_H


// HERE WE DEFINE THE CHECKS REQUIRED FOR FALLING BACK TO THE MINIMUM COMMON INTERFACE (MCI) FOR LOGGER.
// EVERY LOGGER IMPLEMENTATION MUST INCLUDE THESE TWO SETS OF METHODS:
// bool IsCritical() const;
// bool IsDebug() const;
// bool IsError() const;
// bool IsFatal() const;
// bool IsInformation() const;
// bool IsNotice() const;
// bool IsTrace() const;
// bool IsWarning() const;
//
// void Critical(std::string const& msg);
// void Debug(std::string const& msg);
// void Error(std::string const& msg);
// void Fatal(std::string const& msg);
// void Information(std::string const& msg);
// void Notice(std::string const& msg);
// void Trace(std::string const& msg);
// void Warning(std::string const& msg);
//
// THE FIRST SET OF METHODS IS ABSOLUTE, I.E., THERE IS NO CONTINGENCY FOR OVERLOADS IN THAT SET. IF YOU NEED,
// ROLL IT.
//
// FOR THE SECOND SET, THE TEMPLATES BELOW WILL ALLOW US TO DETECT IF THE LIB REQUIRED INTERFACE IS IMPLEMENTED,
// AND, IF IT ISN'T, FALL BACK TO THE MCI, WHICH *MUST* BE IMPLEMENTED.

/*
template<typename T, typename RESULT, typename ARG1, typename ARG2>
class HasCritical
{
    template <typename U, RESULT (U::*)(ARG1, ARG2)> struct Check;
    template <typename U> static char CheckFn(Check<U, &U::Critical> *);
    template <typename U> static int CheckFn(...);
  public:
    enum { value = sizeof(CheckFn<T>(0)) == sizeof(char) };
};
*/

#define CHECK_LIBLOGGER_INTERFACE(Method) \
    template<typename T, typename RESULT, typename ARG1, typename ARG2> \
    class Does##Method \
    { \
        template <typename U, RESULT (U::*)(ARG1, ARG2)> struct Check; \
        template <typename U> static char CheckFn(Check<U, &U::Method> *); \
        template <typename U> static int CheckFn(...); \
      public: \
        enum { Exist = sizeof(CheckFn<T>(0)) == sizeof(char) }; \
    }

CHECK_LIBLOGGER_INTERFACE(Critical);
CHECK_LIBLOGGER_INTERFACE(Debug);
CHECK_LIBLOGGER_INTERFACE(Error);
CHECK_LIBLOGGER_INTERFACE(Fatal);
CHECK_LIBLOGGER_INTERFACE(Information);
CHECK_LIBLOGGER_INTERFACE(Notice);
CHECK_LIBLOGGER_INTERFACE(Trace);
CHECK_LIBLOGGER_INTERFACE(Warning);

#endif // CHECKLIBINTERFACE_H
