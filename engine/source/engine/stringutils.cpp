#include "stdafx.h"
#include "stringutils.h"

ENGINE_NAMESPACE_BEGIN
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool StringUtils::ends_with(string haystack, string needle)
{
    if (needle.length() > haystack.length()) {
        return false;
    }
    else {
        return (haystack.compare(haystack.length() - needle.length(), needle.length(), needle) == 0);
    }
}

ENGINE_NAMESPACE_END