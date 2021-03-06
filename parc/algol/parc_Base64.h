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
 * @file parc_Base64.h
 * @ingroup inputoutput
 * @brief Encode/decode base64
 *
 * Encoding goes to one long line, no line breaks.
 * Decoding will accept CRLF linebreaks in the data and skip them.
 *
 * Following the language of RFC 4648, encoding proceeds in a "quantum" of
 * 3 bytes of plaintext to 4 bytes of encoded data.  Decoding goes in
 * a 4-byte quantum to 3-byte decoded data.
 *
 * If decoding fails (e.g. there's a non-base64 character), then the output
 * buffer is rewound to the starting position and a failure is indicated.
 *
 * Decoding using a 256 byte table.  Each byte of the 4-byte quantum is looked
 * up and if its a valid character -- it resolves to a value 0..63, then that
 * value is shifted to the right position in the output.  Values CR and LF have
 * the special token "_" in the table, which means "skip".  That token has value
 * ascii value 95, is we can detect it as outside base64.  Similarly, all the
 * invalid characters have the symbol "~", which is ascii 127.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef libparc_parc_Base64_h
#define libparc_parc_Base64_h

#include <parc/algol/parc_Buffer.h>
#include <parc/algol/parc_BufferComposer.h>

/**
 * Encode the plaintext buffer to base64, as per RFC 4648, Section 4.
 *
 * The base64 encoding is appended to `output` at the current position, and `output` is returned.
 *
 * @param [in,out] output The instance of {@link PARCBufferComposer} to which the encoded @plainText is appended
 * @param [in] plainText The text to encode and append to @p output
 *
 * @return  A pointer to the @p output
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 *
 */
PARCBufferComposer *parcBase64_Encode(PARCBufferComposer *output, PARCBuffer *plainText);

/**
 * Encode the array to base64.
 *
 * @param [in,out] output The instance of {@link PARCBufferComposer} to which the encoded @p array is appended
 * @param [in] length The length of the Array to be encoded
 * @param array The array to be encoded and appended to @p output
 *
 * @return  A pointer to the @p output
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCBufferComposer *parcBase64_EncodeArray(PARCBufferComposer *output, size_t length, const uint8_t array[length]);

/**
 * Base64 decode the @p encodedText and append the result to @p output,
 * which is returned by the function.
 *
 * If the @p encodedText cannot be base64 decoded,
 * @p output is reset to the starting position and the function returns NULL.
 *
 * @param [in,out] output The instance of {@link PARCBufferComposer} to which the decoded @p encodedText is appended
 * @param [in] encodedText The array to be decoded and appended to @p output
 *
 * @return  A pointer to the @p output, or NULL if the @p encodedText cannot be base64 decoded
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCBufferComposer *parcBase64_Decode(PARCBufferComposer *output, PARCBuffer *encodedText);

/**
 * Base64 decode the string, using strlen() to get the length.
 *
 * @param [in,out] output The instance of {@link PARCBufferComposer} to which the decoded @p encodedText is appended
 * @param [in] encodedString The string to be decoded and appended to @p output
 *
 * @return  A pointer to the @p output, or NULL if the @p encodedString cannot be base64 decoded
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCBufferComposer *parcBase64_DecodeString(PARCBufferComposer *output, const char *encodedString);

/**
 * Base64 decode the array.
 *
 * @param [in,out] output The instance of {@link PARCBufferComposer} to which the decoded @p array is appended
 * @param [in] length The size of the array.
 * @param [in] array The array to be decoded and appended to @p output
 *
 * @return  A pointer to the @p output, or NULL if the @p encodedString cannot be base64 decoded
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCBufferComposer *parcBase64_DecodeArray(PARCBufferComposer *output, size_t length, const uint8_t array[length]);
#endif // libparc_parc_Base64_h
