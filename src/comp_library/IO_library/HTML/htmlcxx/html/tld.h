/** Do not modify. This file is automatically generated
 * using gen_tld.pl and tld.list
 */

static const char *tld[] = {
  ".LOCALHOST",
  ".INVALID",
  ".EXAMPLE",
  ".MUSEUM",
  ".TEST",
  ".NAME",
  ".INFO",
  ".COOP",
  ".ARPA",
  ".AERO",
  ".PRO",
  ".ORG",
  ".NET",
  ".MIL",
  ".INT",
  ".GOV",
  ".EDU",
  ".COM",
  ".BIZ",
  ".ZW",
  ".ZM",
  ".ZA",
  ".YU",
  ".YT",
  ".YE",
  ".WS",
  ".WF",
  ".VU",
  ".VN",
  ".VI",
  ".VG",
  ".VE",
  ".VC",
  ".VA",
  ".UZ",
  ".UY",
  ".US",
  ".UM",
  ".UK",
  ".UG",
  ".UA",
  ".TZ",
  ".TW",
  ".TV",
  ".TT",
  ".TR",
  ".TP",
  ".TO",
  ".TN",
  ".TM",
  ".TK",
  ".TJ",
  ".TH",
  ".TG",
  ".TF",
  ".TD",
  ".TC",
  ".SZ",
  ".SY",
  ".SV",
  ".SU",
  ".ST",
  ".SR",
  ".SO",
  ".SN",
  ".SM",
  ".SL",
  ".SK",
  ".SJ",
  ".SI",
  ".SH",
  ".SG",
  ".SE",
  ".SD",
  ".SC",
  ".SB",
  ".SA",
  ".RW",
  ".RU",
  ".RO",
  ".RE",
  ".QA",
  ".PY",
  ".PW",
  ".PT",
  ".PS",
  ".PR",
  ".PN",
  ".PM",
  ".PL",
  ".PK",
  ".PH",
  ".PG",
  ".PF",
  ".PE",
  ".PA",
  ".OM",
  ".NZ",
  ".NU",
  ".NR",
  ".NP",
  ".NO",
  ".NL",
  ".NI",
  ".NG",
  ".NF",
  ".NE",
  ".NC",
  ".NA",
  ".MZ",
  ".MY",
  ".MX",
  ".MW",
  ".MV",
  ".MU",
  ".MT",
  ".MS",
  ".MR",
  ".MQ",
  ".MP",
  ".MO",
  ".MN",
  ".MM",
  ".ML",
  ".MK",
  ".MH",
  ".MG",
  ".MD",
  ".MC",
  ".MA",
  ".LY",
  ".LV",
  ".LU",
  ".LT",
  ".LS",
  ".LR",
  ".LK",
  ".LI",
  ".LC",
  ".LB",
  ".LA",
  ".KZ",
  ".KY",
  ".KW",
  ".KR",
  ".KP",
  ".KN",
  ".KM",
  ".KI",
  ".KH",
  ".KG",
  ".KE",
  ".JP",
  ".JO",
  ".JM",
  ".JE",
  ".IT",
  ".IS",
  ".IR",
  ".IQ",
  ".IO",
  ".IN",
  ".IM",
  ".IL",
  ".IE",
  ".ID",
  ".HU",
  ".HT",
  ".HR",
  ".HN",
  ".HM",
  ".HK",
  ".GY",
  ".GW",
  ".GU",
  ".GT",
  ".GS",
  ".GR",
  ".GQ",
  ".GP",
  ".GN",
  ".GM",
  ".GL",
  ".GI",
  ".GH",
  ".GG",
  ".GF",
  ".GE",
  ".GD",
  ".GB",
  ".GA",
  ".FR",
  ".FO",
  ".FM",
  ".FK",
  ".FJ",
  ".FI",
  ".ET",
  ".ES",
  ".ER",
  ".EH",
  ".EG",
  ".EE",
  ".EC",
  ".DZ",
  ".DO",
  ".DM",
  ".DK",
  ".DJ",
  ".DE",
  ".CZ",
  ".CY",
  ".CX",
  ".CV",
  ".CU",
  ".CR",
  ".CO",
  ".CN",
  ".CM",
  ".CL",
  ".CK",
  ".CI",
  ".CH",
  ".CG",
  ".CF",
  ".CD",
  ".CC",
  ".CA",
  ".BZ",
  ".BY",
  ".BW",
  ".BV",
  ".BT",
  ".BS",
  ".BR",
  ".BO",
  ".BN",
  ".BM",
  ".BJ",
  ".BI",
  ".BH",
  ".BG",
  ".BF",
  ".BE",
  ".BD",
  ".BB",
  ".BA",
  ".AZ",
  ".AW",
  ".AU",
  ".AT",
  ".AS",
  ".AR",
  ".AQ",
  ".AO",
  ".AN",
  ".AM",
  ".AL",
  ".AI",
  ".AG",
  ".AF",
  ".AE",
  ".AD",
  ".AC"
};
static unsigned int tldOffset(const char *domain) {
  const char *end = domain + strlen(domain);
  for(unsigned int i = 0; i < 264; ++i) {
    unsigned int len = (unsigned int)strlen(tld[i]);
    if(strcasecmp(end - len, tld[i]) == 0) {
      return len;
    }
  }
  return 0;}
