/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <LongBow/runtime.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_SafeMemory.h>
#include <parc/algol/parc_Vector.h>

struct parc_vector {
    const void *pointer;
    size_t length;
};

PARCVector *
parcVector_Create(const void *pointer, const size_t length)
{
    PARCVector *result = parcMemory_AllocateAndClear(sizeof(PARCVector));
    if (result != NULL) {
        parcVector_Init(result, pointer, length);
    }

    return result;
}

PARCVector *
parcVector_Init(PARCVector *vector, const void *pointer, const size_t length)
{
    assertNotNull(vector, "Parameter must be a non-null PARCVector pointer");

    vector->pointer = pointer;
    vector->length = length;
    return vector;
}

void
parcVector_Destroy(PARCVector **vectorPtr)
{
    assertNotNull(vectorPtr, "Parameter must be a non-null PARCVector pointer");
    PARCVector *vector = *vectorPtr;
    assertNotNull(vector, "Vector is already free or was not set.\n");

    parcMemory_Deallocate((void **) &vector);
    *vectorPtr = NULL;
}

const void *
parcVector_GetPointer(const PARCVector *vector)
{
    assertNotNull(vector, "Parameter must be a non-null PARCVector pointer.");
    return vector->pointer;
}

size_t
parcVector_GetLength(const PARCVector *vector)
{
    assertNotNull(vector, "Parameter must be a non-null PARCVector pointer.");

    return vector->length;
}

