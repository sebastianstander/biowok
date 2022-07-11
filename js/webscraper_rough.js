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

// load youtube
// 

search = driver.find_element_by_id('search')            //1
driver.find_element_by_id('search-icon-legacy').click() //2
time.sleep(20)
video_title = driver.find_elements_by_id('video-title')
subscription = driver.find_elements_by_id('byline')
views = driver.find_elements_by_xpath('//div[@id="metadata-line"]/span[1]')
posted = driver.find_elements_by_xpath('//div[@id="metadata-line"]/span[1]')
while( top_count<10 ){
    href.append(vtitle[top_count].get_attribute('href'))
    channel.append(subscription[top_count].get_attribute('title'))
    title.append(vtitle[top_count].text)
    viewcounts.append(views[top_count].text)
    postdate.append(posted[top_count].text)
    top_count = top_count + 1
}


(async function scrape(){
    try {
        let search = await driver.findElement(By.id('search'));   
        let searchButton = await driver.findElement(By.id('search-icon-legacy'));   
        await searchButton.click();
        

    } catch(error) { console.log(error) }
})();