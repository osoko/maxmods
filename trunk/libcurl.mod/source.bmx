' Copyright (c) 2007-20131 Bruce A Henderson
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.

SuperStrict

Import "src/ares/*.h"

Import "src/include/*.h"
Import "src/lib/*.h"

Import "src/lib/file.c"
Import "src/lib/timeval.c"
Import "src/lib/base64.c"
Import "src/lib/hostip.c"
Import "src/lib/progress.c"
Import "src/lib/formdata.c"
Import "src/lib/cookie.c"
Import "src/lib/http.c"
Import "src/lib/sendf.c"
Import "src/lib/ftp.c"
Import "src/lib/url.c"
Import "src/lib/dict.c"
Import "src/lib/if2ip.c"
Import "src/lib/speedcheck.c"
Import "src/lib/ldap.c"
Import "src/lib/ssluse.c"
Import "src/lib/version.c"
Import "src/lib/getenv.c"
Import "src/lib/escape.c"
Import "src/lib/mprintf.c"
Import "src/lib/telnet.c"
Import "src/lib/netrc.c"
Import "src/lib/getinfo.c"
Import "src/lib/transfer.c"
Import "src/lib/strequal.c"
Import "src/lib/easy.c"
Import "src/lib/security.c"
Import "src/lib/krb4.c"
Import "src/lib/curl_fnmatch.c"
Import "src/lib/fileinfo.c"
Import "src/lib/ftplistparser.c"
Import "src/lib/wildcard.c"
Import "src/lib/krb5.c"
Import "src/lib/memdebug.c"
Import "src/lib/http_chunks.c"
Import "src/lib/strtok.c"
Import "src/lib/connect.c"
Import "src/lib/llist.c"
Import "src/lib/hash.c"
Import "src/lib/multi.c"
Import "src/lib/content_encoding.c"
Import "src/lib/share.c"
Import "src/lib/http_digest.c"
Import "src/lib/md4.c"
Import "src/lib/md5.c"
Import "src/lib/curl_rand.c"
Import "src/lib/http_negotiate.c"
'Import "src/lib/http_ntlm.c"
Import "src/lib/inet_pton.c"
Import "src/lib/strtoofft.c"
Import "src/lib/strerror.c"
Import "src/lib/hostasyn.c"
Import "src/lib/hostip4.c"
Import "src/lib/hostip6.c"
Import "src/lib/hostsyn.c"
Import "src/lib/inet_ntop.c"
Import "src/lib/parsedate.c"
Import "src/lib/select.c"
Import "src/lib/gtls.c"
Import "src/lib/sslgen.c"
Import "src/lib/tftp.c"
Import "src/lib/splay.c"
Import "src/lib/strdup.c"
Import "src/lib/socks.c"
Import "src/lib/ssh.c"
Import "src/lib/nss.c"
Import "src/lib/qssl.c"
Import "src/lib/rawstr.c"
Import "src/lib/curl_addrinfo.c"
Import "src/lib/socks_gssapi.c"
Import "src/lib/socks_sspi.c"
Import "src/lib/curl_sspi.c"
Import "src/lib/slist.c"
Import "src/lib/nonblock.c"
Import "src/lib/curl_memrchr.c"
Import "src/lib/imap.c"
Import "src/lib/pop3.c"
Import "src/lib/smtp.c"
Import "src/lib/pingpong.c"
Import "src/lib/rtsp.c"
Import "src/lib/curl_threads.c"
Import "src/lib/warnless.c"
Import "src/lib/hmac.c"
Import "src/lib/polarssl.c"
Import "src/lib/curl_rtmp.c"
Import "src/lib/openldap.c"
Import "src/lib/curl_gethostname.c"
Import "src/lib/gopher.c"
Import "src/lib/axtls.c"
Import "src/lib/idn_win32.c"
Import "src/lib/http_negotiate_sspi.c"
Import "src/lib/cyassl.c"
Import "src/lib/http_proxy.c"
Import "src/lib/non-ascii.c"
Import "src/lib/asyn-ares.c"
Import "src/lib/asyn-thread.c"
Import "src/lib/curl_multibyte.c"
Import "src/lib/curl_ntlm.c"
Import "src/lib/curl_ntlm_core.c"
Import "src/lib/curl_ntlm_msgs.c"
Import "src/lib/curl_ntlm_wb.c"
Import "src/lib/curl_sasl.c"
Import "src/lib/curl_schannel.c"
Import "src/lib/bundles.c"
Import "src/lib/conncache.c"
Import "src/lib/pipeline.c"

' ares
Import "src/ares/ares_fds.c"
Import "src/ares/ares_getsock.c"
Import "src/ares/ares_process.c"
Import "src/ares/ares_free_hostent.c"
Import "src/ares/ares_query.c"
Import "src/ares/ares__close_sockets.c"
Import "src/ares/ares_free_string.c"
Import "src/ares/ares_search.c"
Import "src/ares/ares__get_hostent.c"
Import "src/ares/ares_gethostbyaddr.c"
Import "src/ares/ares_send.c"
Import "src/ares/ares__read_line.c"
Import "src/ares/ares_gethostbyname.c"
Import "src/ares/ares_strerror.c"
Import "src/ares/ares_cancel.c"
Import "src/ares/ares_init.c"
Import "src/ares/ares_timeout.c"
Import "src/ares/ares_destroy.c"
Import "src/ares/ares_mkquery.c"
Import "src/ares/ares_version.c"
Import "src/ares/ares_expand_name.c"
Import "src/ares/ares_parse_a_reply.c"
Import "src/ares/windows_port.c"
Import "src/ares/ares_expand_string.c"
Import "src/ares/ares_parse_ptr_reply.c"
Import "src/ares/ares_parse_aaaa_reply.c"
Import "src/ares/ares_parse_naptr_reply.c"
Import "src/ares/ares_parse_soa_reply.c"
Import "src/ares/ares_getnameinfo.c"
Import "src/ares/inet_net_pton.c"
Import "src/ares/bitncmp.c"
Import "src/ares/ares_inet_ntop.c" ' rename from inet_ntop.c
Import "src/ares/ares_parse_ns_reply.c"
Import "src/ares/ares_llist.c"
Import "src/ares/ares_writev.c"
Import "src/ares/ares_strdup.c"
Import "src/ares/ares_strcasecmp.c"
Import "src/ares/ares_getopt.c"
Import "src/ares/ares__timeval.c"
'Import "src/ares/acountry.c" is a program!
Import "src/ares/ares_data.c"
Import "src/ares/ares_getenv.c"
Import "src/ares/ares_library_init.c"
Import "src/ares/ares_nowarn.c"
Import "src/ares/ares_options.c"
Import "src/ares/ares_parse_mx_reply.c"
Import "src/ares/ares_parse_srv_reply.c"
Import "src/ares/ares_parse_txt_reply.c"
Import "src/ares/ares_platform.c"
Import "src/ares/ares_create_query.c"
