#ifndef LULE_EXCEPTIONS_H
#define LULE_EXCEPTIONS_H

#define LULE_COLLECT_EDATA()   (LULE::ExceptionData(__FILE__, __LINE__))
#define LULE_COLLECT_EDATA_MSG(x)   (LULE::ExceptionData(__FILE__, __LINE__, x))

#define LULE_EXCEPT_OVERRIDE_WHAT(what) public: const LCHAR* What() override { return what; }

namespace LULE {
    struct LULE_API ExceptionData {
        char const* const File = 0;
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
    public:
        LULE_EXCEPT_OVERRIDE_WHAT("Pointer was null.");
    };
}

#endif // !LULE_EXCEPTIONS_H
