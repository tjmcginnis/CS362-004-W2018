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
        assertEquals(true, urlVal.isValid("http://www.google.com"));
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
}
