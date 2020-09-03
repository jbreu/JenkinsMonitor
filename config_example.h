// Rename to config.h

const char* ssid        = "WIFI_ID";
const char* password    = "WIFI_PASSWORD";
const char* host        = "example.org";
const char* url         = "/jenkins/job/PROJECT/job/REPO/job/master/lastBuild/api/json";
const char* reduction   = "?tree=healthReport[score]";                                    //Reduces the amount of returned json data to only the needed parts
const char* token       = "amFrb2I384E4OTE0MGFkYjQyMGQ3Nz2894FlNzc0NzAwNTGDSWZjYg==";
const char* clientcert  = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDzzCCAregAwIBAgIIGTVTgz6KPPgwDQYJKoZIhvcNAQELBQAwQzELMAkGA1UE
................................................................
KUqcXN4SDRQdocKEZavlJoX7yAQj63+6+qDj29t5HinWkD3rDM79YAw1pSpAm07+
8Lw4f7n6fhdOOYubO1ptOAqX2A==
-----END CERTIFICATE-----
)EOF";
const char* clientkey  = R"KEY(
-----BEGIN PRIVATE KEY-----
MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQC02MFb5xI+iTBL
................................................................
yYDBodHoGLo6DE+Bt7RViM57xJYjf9ruK/OWsNJVGZG3mYBm5RVEkiVwU/950cis
vhjt1FEahd2G4F+TW+xMJw==
-----END PRIVATE KEY-----
)KEY";
uint8_t newMACAddress[] = {0xA4, 0xAE, 0xA4, 0xA7, 0xC7, 0x56};
