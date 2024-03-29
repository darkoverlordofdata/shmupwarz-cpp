#include <iostream> 
#include <iomanip>
#include <string> 
//https://stackoverflow.com/questions/37956090/string-interpolation-in-c-construct-a-stdstring-with-embedded-values-e-g

// std::string const word    = "Beautiful";
// std::string const message = CString::format("%0 is a %1 word with %2 characters.\n%0 %2 %0 %1 %2", word, "beautiful", word.size()); 
// Prints:
//   Beautiful is a beautiful word with 9 characters. 
//   Beautiful 9 Beautiful beautiful 9.
/**
 * The CString class provides helpers to convert 8 and 16-bit
 * strings to each other or format a string with a variadic number
 * of arguments.
 */
class CString
{
    public:
    /**
     * Format a string based on 'aFormat' with a variadic number of arbitrarily typed arguments.
     *
     * @param aFormat
     * @param aArguments
     * @return
     */
    template <typename... TArgs>
    static std::string format(
            std::string const&aFormat,
            TArgs        &&...aArguments);

    /**
     * Accept an arbitrarily typed argument and convert it to it's proper
     * string representation.
     *
     * @tparam TArg
     * @tparam TEnable
     * @param aArg
     * @return
     */
    template <
            typename TArg,
            typename TEnable = void
            >
    static std::string toString(TArg const &aArg);

    /**
     * Accept a float argument and convert it to it's proper string representation.
     *
     * @tparam TArg
     * @param arg
     * @return
     */
    template <
            typename TArg,
            typename std::enable_if<std::is_floating_point<TArg>::value, TArg>::type
            >
    static std::string toString(const float& arg);


    /**
     * Convert a string into an arbitrarily typed representation.
     *
     * @param aString
     * @return
     */
    template <
            typename TData,
            typename TEnable = void
            >
    static TData const fromString(std::string const &aString);


    template <
            typename TData,
            typename std::enable_if
                     <
                        std::is_integral<TData>::value || std::is_floating_point<TData>::value,
                        TData
                     >::type
            >
    static TData fromString(std::string const &aString);

private:
    /**
     * Format a list of arguments. In this case zero arguments as the abort-condition
     * of the recursive expansion of the parameter pack.
     *
     * @param aArguments
     */
    template <std::size_t NArgs>
    static void formatArguments(std::array<std::string, NArgs> const &aArguments);

    /**
     * Format a list of arguments of arbitrary type and expand recursively.
     *
     * @param outFormatted
     * @param inArg
     * @param inArgs
     */
    template <
            std::size_t NArgs,
            typename    TArg,
            typename... TArgs
            >
    static void formatArguments(
            std::array<std::string, NArgs>     &aOutFormatted,
            TArg                              &&aInArg,
            TArgs                          &&...aInArgs);
};
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <typename... TArgs>
std::string CString::format(
        const std::string     &aFormat,
        TArgs             &&...aArgs)
{
    std::array<std::string, sizeof...(aArgs)> formattedArguments{};

    formatArguments(formattedArguments, std::forward<TArgs>(aArgs)...);

    if constexpr (sizeof...(aArgs) == 0)
    {
        return aFormat;
    }
    else {
        uint32_t number     = 0;
        bool     readNumber = false;

        std::ostringstream stream;

        for(std::size_t k = 0; k < aFormat.size(); ++k)
        {
            switch(aFormat[k])
            {
            case '%':
                readNumber = true;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // Desired behaviour to enable reading numbers in text w/o preceding %
                #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
                if(readNumber)
                {
                    number *= 10;
                    number += static_cast<uint32_t>(aFormat[k] - '0');
                    break;
                }
            default:
                if(readNumber)
                {
                    stream << formattedArguments[std::size_t(number)];
                    readNumber = false;
                    number     = 0;
                }

                stream << aFormat[k];
                break;
                #pragma GCC diagnostic warning "-Wimplicit-fallthrough"
            }
        }

        if(readNumber)
        {
            stream << formattedArguments[std::size_t(number)];
            readNumber = false;
            number     = 0;
        }

        return stream.str();
    }
}
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <typename TArg, typename enable>
std::string CString::toString(TArg const &aArg)
{
    std::ostringstream stream;
    stream << aArg;
    return stream.str();
}
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <
        typename TArg,
        typename std::enable_if<std::is_floating_point<TArg>::value, TArg>::type
        >
std::string CString::toString(const float& arg) {
    std::ostringstream stream;
    stream << std::setprecision(12) << arg;
    return stream.str();
}
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <std::size_t argCount>
void CString::formatArguments(std::array<std::string, argCount> const&aArgs)
{
    // Unused: aArgs
}
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <std::size_t argCount, typename TArg, typename... TArgs>
void CString::formatArguments(
        std::array<std::string, argCount>     &outFormatted,
        TArg                                 &&inArg,
        TArgs                             &&...inArgs)
{
    // Executed for each, recursively until there's no param left.
    uint32_t const index = (argCount - 1 - sizeof...(TArgs));
    outFormatted[index] = toString(inArg);

    formatArguments(outFormatted, std::forward<TArgs>(inArgs)...);
}
//<-----------------------------------------------------------------------------

//<-----------------------------------------------------------------------------
//<
//<-----------------------------------------------------------------------------
template <
        typename TData,
        typename std::enable_if
                 <
                    std::is_integral<TData>::value || std::is_floating_point<TData>::value,
                    TData
                 >::type
        >
TData CString::fromString(std::string const &aString)
{
    TData const result{};

    std::stringstream ss(aString);
    ss >> result;

    return result;
}
//<-----------------------------------------------------------------------------
