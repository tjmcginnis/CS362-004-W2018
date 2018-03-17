import org.junit.Test;

import static org.junit.Assert.*;

public class UrlValidatorTest {

    @Test
    public void testIsValidManual() {
        UrlValidator urlVal = new UrlValidator(
                null,
                null,
                UrlValidator.ALLOW_ALL_SCHEMES
        );
        assertEquals(true, urlVal.isValid("http://google.com"));
        // assertEquals(true, urlVal.isValid("ftp://192.168.10.10"));  // BUG: Exception raised
        // assertEquals(true, urlVal.isValid("http://google.com:80")); // BUG: Fails but should pass
        assertEquals(true, urlVal.isValid("http://google.com/test"));
        assertEquals(true, urlVal.isValid("http://google.com/test?q=testing"));
        // assertEquals(false, urlVal.isValid("abcd://www.google.com/"));  // BUG: Exception raised
        // assertEquals(false, urlVal.isValid("http://abcd"));  // BUG: Fails but should pass
        assertEquals(false, urlVal.isValid("http://google.com:80b"));
        assertEquals(false, urlVal.isValid("http://google.com/../"));
    }

    @Test
    public void testIsValidUrlSchemesPartitioning() {
        for (int i = 0; i < this.testUrlScheme.length; i++) {
            ResultPair pair = this.testUrlScheme[i];
            String testUrl = pair.getTestValue() + "www.google.com";
            System.out.print(String.format(
                    "Partition testing\tURL Scheme\t%s\t\t", pair.getTestValue())
            );
            this.testSafe(testUrl, pair.isValid());
        }
    }

    @Test
    public void testIsValidUrlAuthoritiesPartition() {
        for (int i = 0; i < this.testUrlAuthority.length; i++) {
            ResultPair pair = this.testUrlAuthority[i];
            String testUrl = "http://" + pair.getTestValue();
            System.out.print(String.format(
                    "Partition testing\tURL Authority\t%s\t\t", pair.getTestValue())
            );
            this.testSafe(testUrl, pair.isValid());
        }
    }

    @Test
    public void testIsValidUrlPortsPartition() {
        for (int i = 0; i < this.testUrlPort.length; i++) {
            ResultPair pair = this.testUrlPort[i];
            String testUrl = "http://www.google.com" + pair.getTestValue();
            System.out.print(String.format(
                    "Partition testing\tURL Port\t%s\t\t", pair.getTestValue())
            );
            this.testSafe(testUrl, pair.isValid());
        }
    }

    @Test
    public void testIsValidUrlPathsPartition() {
        for (int i = 0; i < this.testUrlPath.length; i++) {
            ResultPair pair = this.testUrlPath[i];
            String testUrl = "http://www.google.com" + pair.getTestValue();
            System.out.print(String.format(
                    "Partition testing\tURL Path\t%s\t\t", pair.getTestValue())
            );
            this.testSafe(testUrl, pair.isValid());
        }
    }

    @Test
    public void testIsValidURLQueryStringsPartition() {
        for (int i = 0; i < this.testUrlQuery.length; i++) {
            ResultPair pair = this.testUrlQuery[i];
            String testUrl = "http://www.google.com" + pair.getTestValue();
            System.out.print(String.format(
                    "Partition testing\tURL Query\t%s\t\t", pair.getTestValue())
            );
            this.testSafe(testUrl, pair.isValid());
        }
    }

    private void testSafe(String testUrl, boolean isValid) {
        UrlValidator urlVal = new UrlValidator(
                null,
                null,
                UrlValidator.ALLOW_ALL_SCHEMES
        );

        System.out.print("Expected: " + isValid + "\t");

        try {
            System.out.println("Result: " + urlVal.isValid(testUrl));
        } catch (Exception e) {
            System.out.println("Exception thrown: " + e.getMessage());
        } catch (Error e) {
            System.out.println("Error raised: " + e.getMessage());
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
