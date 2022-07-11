const { ChromiumWebDriver } = require('selenium-webdriver');

// Hello World in Selenium(JS)
const {Builder} = require('selenium-webdriver')
(async function hello_selenium(){
    let driver = await new Builder().forBrowser('chrome').build();
    await driver.get('https://selenium.dev');
    await driver.quit();
})();


//Install a Selenium Library(JS) (https://www.selenium.dev/documentation/webdriver/getting_started/install_drivers/)
npm install selenium-webdriver

//ChromiumWebDriver

//Using Driver from Hard-Coded Location(...as opposed to ENV Paths or Driver Management Software) (JS) 
const{Builder} = require('selenum-webdriver');
const chrome = require('selenium-webdriver/chrome');
const { assert } = require('console');
const service = new chrome.ServiceBuilder('path/to/chromedriver');
const driver = new Builder().forBrowser('chrome').setChromeService(service).build();

//Open & Close Browser(Chrome,JS)
///...
(async function openChromeTest(){
    try {
        let options = new chrome.Options();
        let driver = await new Builder().setChromeOptions(options).forBrowser('chrome').build();
        await driver.get('http;//www.google.com');
        await driver.quit();
    } catch(error) {
        console.log(error)
    }
})();

//First Script Tutorial(JS, 8 Components)
const {Builder,By} = require('selenium-webdriver');
const assert = require('assert');
(async function first_script(){
    try {
        let driver = await new Builder().forBrowser('chrome').build();      //1. Start the Session(JS)
        await driver.get('https://www.google.com');                         //2. Take action on browser(JS)         <Navigating : https://www.selenium.dev/documentation/webdriver/browser/navigation/>
        await driver.getTitle();                                            //3. Request browser information(JS)    <Requesting Browser Info : https://www.selenium.dev/documentation/webdriver/browser/>
        await driver.manager().setTimeouts({implicit:1000});                //4. Establish Waiting Strategy(JS)     <Waiting Strategies : https://www.selenium.dev/documentation/webdriver/waits/>
        let searchBox = await driver.findElement(By.name('q'));             //5. Find an element(JS)                <Finding Elements : https://www.selenium.dev/documentation/webdriver/elements/>
        let searchButtion = await driver.findElement(By.name('btnK'));      // |
        await searchBox.sendKeys('Selenium');                               //6. Take action on element(JS)         <Taking Actions : https://www.selenium.dev/documentation/webdriver/elements/interactions/>
        await searchButtion.click();                                        // |
        let value = await searchBox.getAttribute("value");                  //7. Request element information(JS)    <Requesting Element Information : https://www.selenium.dev/documentation/webdriver/elements/information/>
        assert.deepStrictEqual(value,"Selenium")
        await driver.quit();                                                //8. End the session(JS)
    } catch(error) {
        console.log(error)
    }
})();


// WAITS
// Primary issues arise from race conditions

/*<!doctype html>
<meta charset=utf-8>
<title>Race Condition Example</title>
<script>
    var initialised = false ;
    window.addEventListener("load",function(){
        var newElement = document.createElement("p");
        newElement.textContent = "Hello from Javascript!";
        this.document.body.appendChild(newElement);
        initialised=true;
    });
</script>*/

//
await driver.get('file:///race_condition.html');
const element = driver.findElement(By.css('p'));
assert.strictEqual(await element.getText(),'Hello from JavaScript!');



/// JS Has no implict wait function, so here are alternatives...

// JS Callbacks
console.log('one ')
setTimeout(function waitTwoSeconds(){ console.log('two') },2000)
console.log('three')

// JS Promises
function getActualPageTitle(){
    console.log('Fetching page title...')
    let actual_title = "Page no found"
    return actual_title;
}
function verifyPage(){
    return new Promise( function(resolve,reject) {
        let expected_title = "Selenium Playground"
        let actual_title = getActualPageTitle()
        console.log('Verifying page title...')
        if( expected_title === actual_title ){
            resolve('Page title is matching!');
        } else {
            reject('ERROR! Page title is not matching!')
        }
    })
}
let promise = verifyPage();
promise
    .then( res => {console.log(res)} )
    .catch( err => {console.log(err)} )
    .finally( () => console.log('Reached end of execution!') )


Promise.resolve()
    .then(() => console)


// JS Async & Await Functions
//// JS Async Function
async function myFunction(){
    return "Hello World";
}
async function myFunction(){
    return Promise.resolve("Hello world!");
}
//// JS Await Function
async function displayMessage(){
    let promise = new Promise((resolve,reject)=> {
        setTimeout(() => resolve("Hello World!"),3000)
    });
    let result = await promise;
    alert(result);
}
displayMessage();

//// Promise Example translated to Async/Await
function getActualPageTitle(){
    console.log('Fetching page title...')
    let actual_title = "Page not found"
    return actual_title;
}
function verifyPage(){
    return new Promise( function( resolve , reject) {
        let expected_title = "Selenium Playground"
        let actual_title = getActualPageTitle()
        console.log('Verifying page title...')
        if( expected_title === actual_title ){
            resolve('Page title is matching!');
        } else {
            reject('ERROR! Page title is not matching!');
        }
    })
}
async function promise(){
    try{
        const repsonse = await verifyPage();
        console.log(response);
    } catch(err) {
        console.log(err);
    } finally {
        console.log('You have reached the end of execution!')
    }
}

promise();