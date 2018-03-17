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

        /**
         * Valid URLs
         */
        assertEquals(true, urlVal.isValid("http://google.com"));
        // assertEquals(true, urlVal.isValid("ftp://192.168.10.10"));  // BUG: Exception raised
        // assertEquals(true, urlVal.isValid("http://google.com:80")); // BUG: Fails but should pass
        assertEquals(true, urlVal.isValid("http://google.com/test"));
        assertEquals(true, urlVal.isValid("http://google.com/test?q=testing"));

        /**
         * Invalid URLs
         */

        // Invalid URL Scheme
        // assertEquals(false, urlVal.isValid("abcd://www.google.com/"));  // BUG: Exception raised

        // Invalid URL Authority
        // assertEquals(false, urlVal.isValid("http://abcd"));  // BUG: Fails but should pass

        // Invalid Port
        assertEquals(false, urlVal.isValid("http://google.com:80b"));

        // Invalid Path
        assertEquals(false, urlVal.isValid("http://google.com/../"));
    }

    @Test
    public void testIsValidUrlSchemesPartitioning() {


        String[] validUrlSchemes = {"http://", "https://", "ftp://"};
        String[] invalidUrlSchemes = {"abcd://", "http:/", "://"};

        for (int i = 0; i < validUrlSchemes.length; i++) {
            String testUrl = validUrlSchemes[i] + "www.google.com";
            System.out.print("Testing URL Scheme: " + validUrlSchemes[i] + ", ");
            System.out.print("Expecting result: true, ");
            this.testSafe(testUrl);
        }

        for (int i = 0; i < invalidUrlSchemes.length; i++) {
            //assertEquals(true, urlVal.isValid(invalidUrlSchemes[i] + "www.google.com"));
        }
    }

    @Test
    public void testIsValidUrlAuthoritiiesPartition() {
        String[] validUrlAuthorities = {};
        String[] invalidUrlAuthorities = {};
    }

    @Test
    public void testIsValidUrlPortsPartition() {
        String[] validUrlPorts = {};
        String[] invalidUrlPorts = {};
    }

    @Test
    public void testIsValidUrlPathsPartition() {
        String[] validUrlPaths = {};
        String[] invalidUrlPaths = {};
    }

    @Test
    public void testIsValidURLQueryStringsPartition() {
        String[] validUrlQueryStrings = {};
        String[] invalidUrlQueryStrings = {};
    }

    private void testSafe(String testUrl) {
        UrlValidator urlVal = new UrlValidator(
                null,
                null,
                UrlValidator.ALLOW_ALL_SCHEMES
        );

        try {
            System.out.println("Result: " + urlVal.isValid(testUrl));
        } catch (Exception e) {
            System.out.println("Exception thrown: " + e.getMessage());
        } catch (Error e) {
            System.out.println("Error raised: " + e.getMessage());
        }
    }
}
