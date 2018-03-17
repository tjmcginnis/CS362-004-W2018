import org.junit.Test;

public class UrlValidatorTest {

    @Test
    public void testIsValidManual() {
        ResultPair[] testUrls = {
            new ResultPair("http://google.com", true),
            new ResultPair("ftp://192.168.10.10", true),
            new ResultPair("http://google.com:80", true),
            new ResultPair("http://google.com/test", true),
            new ResultPair("http://google.com/test?q=testing", true),
            new ResultPair("abcd://www.google.com/", false),
            new ResultPair("http://abcd", false),
            new ResultPair("http://google.com:80b", false),
            new ResultPair("http://google.com/../", false)
        };

        System.out.println("Manual Testing");
        for (int i = 0; i < testUrls.length; i++) {
            ResultPair pair = testUrls[i];
            String testUrl = pair.item;
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidUrlSchemesPartitioning() {
        System.out.println("Partition testing URL Schemes");
        for (int i = 0; i < this.testUrlScheme.length; i++) {
            ResultPair pair = this.testUrlScheme[i];
            String testUrl = pair.item + "www.google.com";
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidUrlAuthoritiesPartition() {
        System.out.println("Partition testing URL Authorities");
        for (int i = 0; i < this.testUrlAuthority.length; i++) {
            ResultPair pair = this.testUrlAuthority[i];
            String testUrl = "http://" + pair.item;
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidUrlPortsPartition() {
        System.out.println("Partition testing URL Ports");
        for (int i = 0; i < this.testUrlPort.length; i++) {
            ResultPair pair = this.testUrlPort[i];
            String testUrl = "http://www.google.com" + pair.item;
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidUrlPathsPartition() {
        System.out.println("Partition testing URL Paths");
        for (int i = 0; i < this.testUrlPath.length; i++) {
            ResultPair pair = this.testUrlPath[i];
            String testUrl = "http://www.google.com" + pair.item;
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidURLQueryStringsPartition() {
        System.out.println("Partition testing URL Query");
        for (int i = 0; i < this.testUrlQuery.length; i++) {
            ResultPair pair = this.testUrlQuery[i];
            String testUrl = "http://www.google.com" + pair.item;
            this.testSafe(testUrl, pair.valid, false);
        }
    }

    @Test
    public void testIsValidProgrammatic() {
        System.out.println("Programmatic Testing");
        for (int i = 0; i < this.testUrlScheme.length; i++) {
            for (int j = 0; j < this.testUrlAuthority.length; j++) {
                for (int k = 0; k < this.testUrlPort.length; k++) {
                    for (int l = 0; l < this.testUrlPath.length; l++) {
                        for (int m = 0; m < this.testUrlQuery.length; m++) {
                            String testUrl = this.testUrlScheme[i].item +
                                    this.testUrlAuthority[j].item +
                                    this.testUrlPort[k].item +
                                    this.testUrlPath[l].item +
                                    this.testUrlQuery[m].item;
                            boolean result = this.testUrlScheme[i].valid &&
                                    this.testUrlAuthority[j].valid &&
                                    this.testUrlPort[k].valid &&
                                    this.testUrlPath[l].valid &&
                                    this.testUrlQuery[m].valid;
                            this.testSafe(testUrl, result, false);
                        }
                    }
                }
            }
        }
    }

    private void testSafe(String testUrl, boolean isValid, boolean isNoisy) {
        boolean result;
        UrlValidator urlVal = new UrlValidator(
                null,
                null,
                UrlValidator.ALLOW_ALL_SCHEMES
        );

        String output = String.format("Testing: %s", testUrl);
        output += "\tExpecting: " + isValid;

        try {
            result = urlVal.isValid(testUrl);
            output += "\tResult: " + result;
            if (isNoisy || (result != isValid)) {
                System.out.println(output);
            }
        } catch (Exception e) {
            output += "\tException thrown: " + e.getMessage();
            System.out.println(output);
        } catch (Error e) {
            output += "\tError raised: " + e.getMessage();
            System.out.println(output);
        }
    }

    private ResultPair[] testUrlScheme = {
            new ResultPair("http://", true),
            new ResultPair("https://", true),
            new ResultPair("ftp://", true),
            new ResultPair("https:", false),
            new ResultPair("https/", false),
            new ResultPair("://", false),
            new ResultPair("/", false),
            new ResultPair(":", false),
            new ResultPair("333", false),
            new ResultPair("!!", false)
    };

    private ResultPair[] testUrlAuthority = {
            new ResultPair("www.google.com", true),
            new ResultPair("google.com", true),
            new ResultPair("google.jp", true),
            new ResultPair("192.168.0.2", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("333.444.555.666", false),
            new ResultPair("1.1.1.256", false),
            new ResultPair("1000.10.10.10", false),
            new ResultPair("....", false),
            new ResultPair("foo", false),
            new ResultPair("999", false),
            new ResultPair(".b.a.d.", false)
    };

    private ResultPair[] testUrlPort = {
            new ResultPair("", true),
            new ResultPair(":80", true),
            new ResultPair(":0", true),
            new ResultPair(":65535", true),
            new ResultPair(":65535", true),
            new ResultPair(":808080", false),
            new ResultPair(":2b", false),
            new ResultPair(":2B", false),
            new ResultPair(":34C", false),
            new ResultPair(":8ABCDE", false),
            new ResultPair(":!!!", false),
            new ResultPair(":-1", false)
    };

    private ResultPair[] testUrlPath = {
            new ResultPair("", true),
            new ResultPair("/foo", true),
            new ResultPair("/.", true),
            new ResultPair("/..", false),
            new ResultPair("/...", false),
            new ResultPair("/../", false),
            new ResultPair("/sna//foo", true),
            new ResultPair("/../foo", false),
            new ResultPair("/..//foo", false),
            new ResultPair("/#/item", false),
            new ResultPair("/#", false),
            new ResultPair("/foo/bar", true),
            new ResultPair("/sna/foo/bar", true)
    };

    private ResultPair[] testUrlQuery = {
            new ResultPair("", true),
            new ResultPair("?action=view", true),
            new ResultPair("?action=delete&item=1", true)
    };
}
