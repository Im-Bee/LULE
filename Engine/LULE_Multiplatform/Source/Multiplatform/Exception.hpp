#ifndef LULE_EXCEPTIONS_H
#define LULE_EXCEPTIONS_H

#define LULE_COLLECT_EDATA() (std::move(LULE::ExceptionData(__FILE__, __LINE__)))
#define LULE_COLLECT_EDATA_MSG(x)   (std::move(LULE::ExceptionData(__FILE__, __LINE__, x)))

#define LULE_EXCEPT_OVERRIDE_CONSTRUCTOR(derivedClass) public: explicit derivedClass(ExceptionData&& data) noexcept : Exception(std::move(data)) {};
#define LULE_EXCEPT_OVERRIDE_WHAT(what) public: const LCHAR* What() override { return what; }
#define LULE_EXCEPT_DECL(derivedClass, what) LULE_EXCEPT_OVERRIDE_CONSTRUCTOR(derivedClass); LULE_EXCEPT_OVERRIDE_WHAT(what);

namespace LULE {
    struct LULE_API ExceptionData {
        char const* const File = "Unkonwn";
        const LUINT32& Line = -1;
        char Message[LMEM_KiB(LQUARTER)] = { 0 };
    };

    class LULE_API Exception {
        ExceptionData m_Data;
        LWCHAR m_szRaportLocation[LULE_PATH_MAX_SIZE] = { 0 };

    public:
        Exception() noexcept {
            PopUp(Raport());
        }

        explicit Exception(ExceptionData&& data) noexcept;
        ~Exception() noexcept = default;

        Exception(const Exception&) noexcept = default;
        Exception(Exception&&) noexcept = default;

        virtual const LCHAR* What() { return "Not specified."; }

    private:
        /*
        * @returns
        * If raport succeded then returns 0,
        * if raport write falled to "Error.log" then returns 1,
        * if method failed completly then returns 2.
        **/
        LUINT8 Raport();

        void PopUp(const LUINT8& didRaportFailed = 2);
    };

    class LULE_API ExceptionWasNullptr : public LULE::Exception {
        LULE_EXCEPT_DECL(ExceptionWasNullptr, "Pointer was null.")
    };

    class LULE_API ExceptionThreading : public Exception {
        LULE_EXCEPT_DECL(ExceptionThreading, "There was a possible problem related to multithreading.")
    };

    class LULE_API ExceptionOutsideOfScope : public Exception {
        LULE_EXCEPT_DECL(ExceptionOutsideOfScope, "Enumeration or index was outside of scope.")
    };

    class LULE_API ExceptionBadString : public Exception {
        LULE_EXCEPT_DECL(ExceptionBadString, "String wasn't nullterminated or was corrupted.")
    };
}

#endif // !LULE_EXCEPTIONS_H
