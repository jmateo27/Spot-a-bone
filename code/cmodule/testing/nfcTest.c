/*-
 * Free/Libre Near Field Communication (NFC) library
 *
 * Libnfc historical contributors:
 * Copyright (C) 2009      Roel Verdult
 * Copyright (C) 2009-2013 Romuald Conty
 * Copyright (C) 2010-2012 Romain Tartière
 * Copyright (C) 2010-2013 Philippe Teuwen
 * Copyright (C) 2012-2013 Ludovic Rousseau
 * See AUTHORS file for a more comprehensive list of contributors.
 * Additional contributors of this file:
 * Copyright (C) 2020      Adam Laurie
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  1) Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  2 )Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Note that this license only applies on the examples, NFC library itself is under LGPL
 *
 */

/**
 * @file nfc-poll.c
 * @brief Polling example
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <err.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <nfc/nfc.h>
#include <nfc/nfc-types.h>

#include "nfc-utils.h"

#define MAX_DEVICE_COUNT 16

static nfc_device *pnd = NULL;
static nfc_context *context;

    // To compile this simple example:
// $ gcc -o quick_start_example1 quick_start_example1.c -lnfc
// ./quick_start_example1

#include <stdlib.h>
#include <nfc/nfc.h>

void print_nfc_target(const nfc_target *pnt, bool verbose)
{
  char *s;
  str_nfc_target(&s, pnt, verbose);
  printf("%s", s);
  nfc_free(s);
}

int main(int argc, const char *argv[])
{
    nfc_device *pnd;
    nfc_target nt;

    // Allocate only a pointer to nfc_context
    nfc_context *context;

    // Initialize libnfc and set the nfc_context
    nfc_init(&context);
    if (context == NULL) {
      printf("Unable to init libnfc (malloc)\n");
      exit(EXIT_FAILURE);
    }

    // Display libnfc version
    const char *acLibnfcVersion = nfc_version();
    (void)argc;
    printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);

    // Open, using the first available NFC device
    pnd = nfc_open(context, NULL);

    if (pnd == NULL) {
      printf("ERROR: %s\n", "Unable to open NFC device.");
      exit(EXIT_FAILURE);
    }
    // Set opened NFC device to initiator mode
    if (nfc_initiator_init(pnd) < 0) {
      nfc_perror(pnd, "nfc_initiator_init");
      exit(EXIT_FAILURE);
    }

    printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

    nfc_target ant[1];
    nfc_modulation nm;
    nm.nmt = NMT_ISO14443B;
    nm.nbr = NBR_106;

    nfc_initiator_list_passive_targets(pnd,nm,ant,1);
    printf("%s\n",nfc_strerror(pnd)); // print Success

    nfc_target ant2[1];
    nfc_modulation nm2;
    nm2.nmt = NMT_ISO14443B2SR;
    nm2.nbr = NBR_106;

    int res = 0;
    int n = 0;
    res = nfc_initiator_list_passive_targets(pnd, nm2, ant2, 1);
    printf("%s\n",nfc_strerror(pnd)); // print Success

    // printf("Cart identifier: %s\n", nt.nti.nsi.abtUID);
    for (n = 0; n < res; n++) {
      print_nfc_target(&ant2[n], true);
      printf("\n");
    }

    // Close NFC device
    nfc_close(pnd);
    // Release the context
    nfc_exit(context);
    exit(EXIT_SUCCESS);
}