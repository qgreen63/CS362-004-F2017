/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   System.out.println(urlVal.isValid("https://www.amazon.com"));
	   System.out.println(urlVal.isValid("https://oregonstate.instructure.com/courses/1648345"));
	   System.out.println(urlVal.isValid("file:///Users/tim/Downloads/FinalProject%20(1).pdf"));
	   
	   // next set of invalid urls come from:  http://formvalidation.io/validators/uri/
	   System.out.println(urlVal.isValid("http://-a.b.co"));
	   System.out.println(urlVal.isValid("http://"));
	   System.out.println(urlVal.isValid("http://."));
	   System.out.println(urlVal.isValid("http://.."));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("http://../"));
	   System.out.println(urlVal.isValid("http://?"));
	   System.out.println(urlVal.isValid("http://??"));
	   System.out.println(urlVal.isValid("http://??/"));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("http://#"));
	   System.out.println(urlVal.isValid("http://##"));
	   System.out.println(urlVal.isValid("http://##/"));
	   System.out.println(urlVal.isValid("http://foo.bar?q=Spaces should be encoded"));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("//"));
	   System.out.println(urlVal.isValid("//a"));
	   System.out.println(urlVal.isValid("///a"));
	   System.out.println(urlVal.isValid("///"));
	   System.out.println(urlVal.isValid("http:///a"));
	   System.out.println(urlVal.isValid("foo.com"));
	   System.out.println(urlVal.isValid("rdar://1234"));
	   System.out.println(urlVal.isValid("h://test"));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("http:// shouldfail.com"));
	   System.out.println(urlVal.isValid(":// should fail"));
	   System.out.println(urlVal.isValid("http://foo.bar/foo(bar)baz quux"));
	   System.out.println(urlVal.isValid("ftps://foo.bar/"));
	   System.out.println(urlVal.isValid("http://-error-.invalid/"));
	   System.out.println(urlVal.isValid("http://a.b--c.de/")); // passes as true
	   System.out.println(urlVal.isValid("http://-a.b.co"));
	   System.out.println(urlVal.isValid("http://a.b-.co"));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("http://0.0.0.0"));  // passes as true
	   System.out.println(urlVal.isValid("http://10.1.1.0")); // passes as true
	   System.out.println(urlVal.isValid("http://10.1.1.255")); // passes as true
	   System.out.println(urlVal.isValid("http://224.1.1.1")); // passes as true
	   System.out.println(urlVal.isValid("http://1.1.1.1.1"));
	   System.out.println(urlVal.isValid("http://123.123.123"));
	   System.out.println(urlVal.isValid("http://3628126748"));
	   System.out.println(urlVal.isValid("http://.www.foo.bar/"));
	   System.out.println("\n");
	   System.out.println(urlVal.isValid("http://www.foo.bar./")); // passes as true
	   System.out.println(urlVal.isValid("http://.www.foo.bar./")); // passes as true
	   System.out.println(urlVal.isValid("http://10.1.1.1"));
	   System.out.println(urlVal.isValid("http://10.1.1.254"));


	   // these should all pass as valid urls http://formvalidation.io/validators/uri/
	   System.out.println("\n");
	 	System.out.println(urlVal.isValid("http://foo.com/blah_blah"));
		System.out.println(urlVal.isValid("http://foo.com/blah_blah/"));
		System.out.println(urlVal.isValid("http://foo.com/blah_blah_(wikipedia)"));
		System.out.println(urlVal.isValid("http://foo.com/blah_blah_(wikipedia)_(again)"));
		System.out.println(urlVal.isValid("http://www.example.com/wpstyle/?p=364")); // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("https://www.example.com/foo/?bar=baz&inga=42&quux")); // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://✪df.ws/123")); // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid:password@example.com:8080")); // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid:password@example.com:8080/")); // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid@example.com"));  // DOES NOT PASS BUT SHOULD
		System.out.println("\n");

		System.out.println(urlVal.isValid("http://userid@example.com/"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid@example.com:8080"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid@example.com:8080/"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid:password@example.com"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://userid:password@example.com/"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://142.42.1.1/"));
		System.out.println(urlVal.isValid("http://142.42.1.1:8080/"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://➡.ws/䨹"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://⌘.ws"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://⌘.ws/"));  // DOES NOT PASS BUT SHOULD
		System.out.println("\n");

		System.out.println(urlVal.isValid("http://foo.com/blah_(wikipedia)#cite-1"));
		System.out.println(urlVal.isValid("http://foo.com/blah_(wikipedia)_blah#cite-1"));
		System.out.println(urlVal.isValid("http://foo.com/unicode_(✪)_in_parens"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://foo.com/(something)?after=parens"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://☺.damowmow.com/"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://code.google.com/events/#&product=browser"));
		System.out.println(urlVal.isValid("http://j.mp"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("ftp://foo.bar/baz"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://foo.bar/?q=Test%20URL-encoded%20stuff"));  // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://مثال.إختبار"));   // DOES NOT PASS BUT SHOULD
		System.out.println("\n");

		System.out.println(urlVal.isValid("http://例子.测试"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://उदाहरण.परीक्षा"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://-.~_!$&'()*+,;=:%40:80%2f::::::@example.com"));   // DOES NOT PASS BUT SHOULD
		System.out.println(urlVal.isValid("http://a.b-c.de"));
		System.out.println(urlVal.isValid("http://223.255.255.254"));
   }
   
   // Input Partition Testing
   
   // Test IPv4 Addresses
   // This partition includes invalid IP-like strings as well as valid IP addresses,
   // specifically any address consisting solely of '.' delimited
   // non-negative integers.
   public void testIPv4Address()
   {
	   System.out.println("Starting Partition Test for IPv4-like addresses");
	   UrlValidator urlVal = new UrlValidator();
	   
	   // Test lowest and highest valid IP addresses
	   assertTrue(urlVal.isValid("http://0.0.0.0"));
	   assertTrue(urlVal.isValid("http://255.255.255.255"));
	   
	   // Test just above valid range for each part
	   assertFalse(urlVal.isValid("http://256.256.256.256"));
	   
	   // Test wrong number of number groups
	   assertFalse(urlVal.isValid("http://123.123"));
	   assertFalse(urlVal.isValid("http://123.123.123.123.123"));
	   System.out.println("Finished Partition Test for IPv4-like addresses");
   }
   
   // Test basic host names
   // This partition includes only basic url's with a domain name and TLD,
   // with no queries, paths or fragments
   public void testHostNames()
   {
	   System.out.println("Starting Partition Test for basic host addresses");
	   UrlValidator urlVal = new UrlValidator();

	   // Test a simple, valid example
	   assertTrue(urlVal.isValid("http://test.com"));

	   // Test different TLD's. Using the first and last of the list of valid TLD's 
	   // from here: http://data.iana.org/TLD/tlds-alpha-by-domain.txt (As of Dec. 3 2017)
	   assertTrue(urlVal.isValid("http://test.aaa"));
	   assertTrue(urlVal.isValid("http://test.zw"));
	   
	   // Test multiple dots
	   assertTrue(urlVal.isValid("http://te.st.com"));

	   // Test bad TLD
	   assertFalse(urlVal.isValid("http://test.a1"));

	   // Test bad domain name
	   assertFalse(urlVal.isValid("http://-test.com"));
	   System.out.println("Finished Partition Test for basic host addresses");
   }
   
   // Test valid host names with paths
   // This partition includes no queries or fragments
   public void testPath() 
   {
	   System.out.println("Starting Partition Test for basic host addresses with paths");
	   UrlValidator urlVal = new UrlValidator(); 
	   
	   // Test minimum "/" path
	   assertTrue(urlVal.isValid("http://test.com/"));
	   
	   // Test long path
	   assertTrue(urlVal.isValid("http://test.com/this/is/a/foirly/long/path/that/just/goes/on/and/on/and/on/and/on"));
	   
	   // Test invalid path (< and > aren't allowed)
	   assertFalse(urlVal.isValid("http://test.com/<>"));
	   System.out.println("Finished Partition Test for basic host addresses with paths");

   }
   
   // Test url's with queries
   // This partition includes all URL's with queries, but no fragments  
   public void testQuery()
   {
	   System.out.println("Starting Partition Test for basic host addresses with queries");
	   UrlValidator urlVal = new UrlValidator(); 
	   
	   // Test minimum "?" query
	   assertTrue(urlVal.isValid("http://test.com?"));
	   
	   // Test a fairly long query
	   assertTrue(urlVal.isValid("http://test.com?thisisafoirlylongquerythat/just:goes&on;andon")); 
	   
	   //Test a query with a path
	   assertTrue(urlVal.isValid("http://test.com/?"));

	   
   }
   
   // Test url's with queries
   // This partition includes all URL's with Fragments  
   public void testFragment()
   {
	   System.out.println("Starting Partition Test for basic host addresses with Fragments");
	   UrlValidator urlVal = new UrlValidator(); 
	   
	   // Test minimum "#" fragment
	   assertTrue(urlVal.isValid("http://test.com#"));
	   
	   // Test a fairly long fragment
	   assertTrue(urlVal.isValid("http://test.com#thisisafoirlylongfragmentthat/just:goes&on;andon"));
	   
	   //Test a fragment with a path
	   assertTrue(urlVal.isValid("http://test.com/#"));
	   
	   //Test a fragment with a query
	   assertTrue(urlVal.isValid("http://test.com?#"));
	   
	   //Test a fragment with a path and a query
	   assertTrue(urlVal.isValid("http://test.com/?#"));  
	   
	   System.out.println("Ending Partition Test for basic host addresses with Fragments");

   }


   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}