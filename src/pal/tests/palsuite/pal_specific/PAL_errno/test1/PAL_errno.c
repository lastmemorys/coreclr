//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information. 
//

/*=============================================================
**
** Source: pal_errno.c
**
** Purpose: Positive test the PAL_errno API.
**          call PAL_errno to retrieve the pointer to 
**          the per-thread errno value.
**
**
**============================================================*/
#include <palsuite.h>

int __cdecl main(int argc, char *argv[])
{
    int err;
    FILE *pFile = NULL;

    /*Initialize the PAL environment*/
    err = PAL_Initialize(argc, argv);
    if( 0 != err)
    {
        return FAIL;
    }
    
    /*Try to open a not-exist file to read to generate an error*/
    pFile = fopen( "no_exist_file_name", "r" );
    
    if( NULL != pFile )
    {
        Trace("\nFailed to call fopen to open a not exist for reading, "
                "an error is expected, but no error occured\n");

        if( EOF == fclose( pFile ) )
        {
            Trace("\nFailed to call fclose to close a file stream\n");
        }
        Fail( "Test failed! fopen() Should not have worked!" );
    }

    /*retrieve the per-thread error value pointer*/
    if( 2 != errno )
    {
        Fail("\nFailed to call PAL_errno API, this value is not correct."
             " The correct value is ENOENT[2] ( No such file or directory.).\n");
    }
    
    PAL_Terminate();
    return PASS;
}
