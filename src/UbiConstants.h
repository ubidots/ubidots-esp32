
/*
Copyright (c) 2013-2018 Ubidots.
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
Developed and maintained by Jose Garcia and Cristian Arrieta for IoT Services
Inc
@jotathebest at github: https://github.com/jotathebest
@crisap94 at github: https://github.com/crisap94
*/

#ifndef _UbiConstants_H_
#define _UbiConstants_H_

#include "UbiTypes.h"
#include "stdint.h"

const char UBIDOTS_INDUSTRIAL_IP[] = "169.55.61.243";
const char* const USER_AGENT = "UbidotsESP32/0.0.1";
const int UBIDOTS_HTTPS_PORT = 443;
const int UBIDOTS_TCP_PORT = 9012;
const int UBIDOTS_TCPS_PORT = 9812;
const uint8_t MAX_VALUES = 10;
const float ERROR_VALUE = -3.4028235E+8;
const int MAX_BUFFER_SIZE = 700;
static UbiServer UBI_INDUSTRIAL = "industrial.api.ubidots.com";
const char* const NTP_SERVER = "pool.ntp.org";
const char* const NIST_SERVER = "time.nist.gov";

/* Creates the Ubidots cert (available at
https://z.cdn.ubidots.com/ustatic/certs/roots.der) using the command below xxd
-i DigiCertHighAssuranceEVRootCA.crt.der >cacert.h
*/
static const char* UBI_CA_CERT =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIE0TCCA7mgAwIBAgISAwN88L85jnFtBNApk1/75393MA0GCSqGSIb3DQEBCwUA\n"
    "MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD\n"
    "EwJSMzAeFw0yMDEyMjkyMzIyMDBaFw0yMTAzMjkyMzIyMDBaMCUxIzAhBgNVBAMT\n"
    "GmluZHVzdHJpYWwuYXBpLnViaWRvdHMuY29tMFkwEwYHKoZIzj0CAQYIKoZIzj0D\n"
    "AQcDQgAElSEh7Nz5UJMJAgJOi9wf8eZYH7RJoeFFHrF1bk41etuUo5m35ixTeLZA\n"
    "lbGcU9QsXLBV+lIkxZnsFe7uFhmsVqOCArcwggKzMA4GA1UdDwEB/wQEAwIHgDAd\n"
    "BgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIwADAdBgNV\n"
    "HQ4EFgQUdXBH+mnh11Tcknf7cxYE+ZDIzkEwHwYDVR0jBBgwFoAUFC6zF7dYVsuu\n"
    "UAlA5h+vnYsUwsYwVQYIKwYBBQUHAQEESTBHMCEGCCsGAQUFBzABhhVodHRwOi8v\n"
    "cjMuby5sZW5jci5vcmcwIgYIKwYBBQUHMAKGFmh0dHA6Ly9yMy5pLmxlbmNyLm9y\n"
    "Zy8wgYUGA1UdEQR+MHyCGGJ1c2luZXNzLmFwaS51Ymlkb3RzLmNvbYIaaW5kdXN0\n"
    "cmlhbC5hcGkudWJpZG90cy5jb22CG2luZHVzdHJpYWw2LmFwaS51Ymlkb3RzLmNv\n"
    "bYISdGhpbmdzLnViaWRvdHMuY29tghN0aGluZ3M2LnViaWRvdHMuY29tMEwGA1Ud\n"
    "IARFMEMwCAYGZ4EMAQIBMDcGCysGAQQBgt8TAQEBMCgwJgYIKwYBBQUHAgEWGmh0\n"
    "dHA6Ly9jcHMubGV0c2VuY3J5cHQub3JnMIIBBQYKKwYBBAHWeQIEAgSB9gSB8wDx\n"
    "AHYA9lyUL9F3MCIUVBgIMJRWjuNNExkzv98MLyALzE7xZOMAAAF2sQXdYQAABAMA\n"
    "RzBFAiBO6hZwI5sXDyQrSDmtzE1mQAe/+51rgJnXsl1sLeRK8AIhAM3/slAQ6lj4\n"
    "LYOWQQFFxH4YGbV1dBTxBTdXyuv54s0WAHcARJRlLrDuzq/EQAfYqP4owNrmgr7Y\n"
    "yzG1P9MzlrW2gagAAAF2sQXfKAAABAMASDBGAiEAz5SIM2TqFssi1Q8xMiA+0E9b\n"
    "TX34csA3/eYWVjDs/wACIQDIZYDxss7CX6tNpFfCpbc7Fy782w0F8ghfKJvzghVV\n"
    "WzANBgkqhkiG9w0BAQsFAAOCAQEAagVGlUI7xJoSpOVJP7SXuXEtPPE7es1JhSZl\n"
    "yhJGxSh6tqhlI8fc3c4sQX6S9AuRJJlE20c+SQzXM9b2gBxrg1OMHZeeA3sEvPjF\n"
    "isIJNqsMDEx5A97E40beDsfcl+RK/jZvs3+yNGs2/8QAwtzimYEJayJiXyseE07R\n"
    "mdIQakG5nNXbLXnz5luRtRHnVBmh+rW7WSovJ7/ik235/vPc1griwUgYiAd9JWAQ\n"
    "vhS3VQ0xoePFPGhSd1ovooXFhP2+ARsUelzimPe6zHvDSC5rMIgmN3UTjJRzhpmt\n"
    "uwxH53c15gG4m09mjtb+7oDoFNH//Q4EDyI/0g9I4GN3gScUrw==\n"
    "-----END CERTIFICATE-----\n"
    "-----BEGIN CERTIFICATE-----\n"
    "MIIEZTCCA02gAwIBAgIQQAF1BIMUpMghjISpDBbN3zANBgkqhkiG9w0BAQsFADA/\n"
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
    "DkRTVCBSb290IENBIFgzMB4XDTIwMTAwNzE5MjE0MFoXDTIxMDkyOTE5MjE0MFow\n"
    "MjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxCzAJBgNVBAMT\n"
    "AlIzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuwIVKMz2oJTTDxLs\n"
    "jVWSw/iC8ZmmekKIp10mqrUrucVMsa+Oa/l1yKPXD0eUFFU1V4yeqKI5GfWCPEKp\n"
    "Tm71O8Mu243AsFzzWTjn7c9p8FoLG77AlCQlh/o3cbMT5xys4Zvv2+Q7RVJFlqnB\n"
    "U840yFLuta7tj95gcOKlVKu2bQ6XpUA0ayvTvGbrZjR8+muLj1cpmfgwF126cm/7\n"
    "gcWt0oZYPRfH5wm78Sv3htzB2nFd1EbjzK0lwYi8YGd1ZrPxGPeiXOZT/zqItkel\n"
    "/xMY6pgJdz+dU/nPAeX1pnAXFK9jpP+Zs5Od3FOnBv5IhR2haa4ldbsTzFID9e1R\n"
    "oYvbFQIDAQABo4IBaDCCAWQwEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8E\n"
    "BAMCAYYwSwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5p\n"
    "ZGVudHJ1c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTE\n"
    "p7Gkeyxx+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEE\n"
    "AYLfEwEBATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2Vu\n"
    "Y3J5cHQub3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0\n"
    "LmNvbS9EU1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYf\n"
    "r52LFMLGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjANBgkqhkiG9w0B\n"
    "AQsFAAOCAQEA2UzgyfWEiDcx27sT4rP8i2tiEmxYt0l+PAK3qB8oYevO4C5z70kH\n"
    "ejWEHx2taPDY/laBL21/WKZuNTYQHHPD5b1tXgHXbnL7KqC401dk5VvCadTQsvd8\n"
    "S8MXjohyc9z9/G2948kLjmE6Flh9dDYrVYA9x2O+hEPGOaEOa1eePynBgPayvUfL\n"
    "qjBstzLhWVQLGAkXXmNs+5ZnPBxzDJOLxhF2JIbeQAcH5H0tZrUlo5ZYyOqA7s9p\n"
    "O5b85o3AM/OJ+CktFBQtfvBhcJVd9wvlwPsk+uyOy2HI7mNxKKgsBTt375teA2Tw\n"
    "UdHkhVNcsAKX1H7GNNLOEADksd86wuoXvg==\n"
    "-----END CERTIFICATE-----\n";

#endif
