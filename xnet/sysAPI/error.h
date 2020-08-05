#ifndef _XNET_ERROR_H_
#define _XNET_ERROR_H_

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

namespace xnet
{
namespace sys
{
    void error_exit(const char *desp)
    {
        perror(desp);
        exit(1);
    }



} // namespace sys


} // namespace xnet


#endif // !_XNET_ERROR_H_