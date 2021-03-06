/**********************************************************************
 * Copyright (c) 2016 Jonas Schnelli                                  *
 * Distributed under the MIT software license, see the accompanying   *
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#include <btc/base58.h>
#include <btc/chain.h>
#include <btc/tool.h>

#include <btc/utils.h>

#include "utest.h"

void test_tool()
{
    char addr[100];
    u_assert_int_eq(address_from_pubkey(&btc_chain_main, "02fcba7ecf41bc7e1be4ee122d9d22e3333671eb0a3a87b5cdf099d59874e1940f", addr), true);
    u_assert_str_eq(addr, "1Nro9WkpaKm9axmcfPVp79dAJU1Gx7VmMZ");

    size_t pubkeylen = 100;
    char pubkey[pubkeylen];
    u_assert_int_eq(pubkey_from_privatekey(&btc_chain_main, "KxDQjJwvLdNNGhsipGgmceWaPjRndZuaQB9B2tgdHsw5sQ8Rtqje", pubkey, &pubkeylen), true);
    u_assert_str_eq(pubkey, "02fcba7ecf41bc7e1be4ee122d9d22e3333671eb0a3a87b5cdf099d59874e1940f");

    size_t privkeywiflen = 100;
    char privkeywif[privkeywiflen];
    char privkeyhex[100];
    u_assert_int_eq(gen_privatekey(&btc_chain_main, privkeywif, privkeywiflen, NULL), true);
    u_assert_int_eq(gen_privatekey(&btc_chain_main, privkeywif, privkeywiflen, privkeyhex), true);

    uint8_t privkey_data[strlen(privkeywif)];
    size_t outlen = btc_base58_decode_check(privkeywif, privkey_data, sizeof(privkey_data));
    u_assert_int_eq(privkey_data[0] == btc_chain_main.b58prefix_secret_address, true);

    char privkey_hex_or_null[65];
    utils_bin_to_hex(privkey_data+1, BTC_ECKEY_PKEY_LENGTH, privkey_hex_or_null);
    u_assert_str_eq(privkeyhex,privkey_hex_or_null);

    size_t masterkeysize = 200;
    char masterkey[masterkeysize];
    u_assert_int_eq(hd_gen_master(&btc_chain_main, masterkey, masterkeysize), true);
    u_assert_int_eq(hd_print_node(&btc_chain_main, masterkey), true);

    size_t extoutsize = 200;
    char extout[extoutsize];
    u_assert_int_eq(hd_derive(&btc_chain_main, "xprv9s21ZrQH143K2JF8RafpqtKiTbsbaxEeUaMnNHsm5o6wCW3z8ySyH4UxFVSfZ8n7ESu7fgir8imbZKLYVBxFPND1pniTZ81vKfd45EHKX73", "m/1", extout, extoutsize), true);
    u_assert_str_eq(extout, "xprv9tzRNW1ZnrURGVu66TgodMCdZfYms8dVapp4q24RswKY7hChXwrdnbyEFpfz26yVJh5h4zgBWiJ2nD8Qj3oGjjVNtyTFZFUrWQiYwwAfYdg");

    u_assert_int_eq(hd_derive(&btc_chain_main, "xprv9s21ZrQH143K2JF8RafpqtKiTbsbaxEeUaMnNHsm5o6wCW3z8ySyH4UxFVSfZ8n7ESu7fgir8imbZKLYVBxFPND1pniTZ81vKfd45EHKX73", "m/1'", extout, extoutsize), true);
    u_assert_str_eq(extout, "xprv9tzRNW1i8X1PSWBU8w1T7f8xCejSahmGsBLXi2XUqJPF7gLpn99mnuUK9jUKUP9hZbi5bbMCcHKi7MceLJ2ya3ArinuB3rDgcUnSzks1iWk");

    u_assert_int_eq(hd_derive(&btc_chain_main, "xpub661MyMwAqRbcEnKbXcCqD2GT1di5zQxVqoHPAgHNe8dv5JP8gWmDproS6kFHJnLZd23tWevhdn4urGJ6b264DfTGKr8zjmYDjyDTi9U7iyT", "m/1", extout, extoutsize), true);
    
}
