const {Build,By,until, Builder} = require('selenium-webdriver');
const assert = require('assert');

(async function _ (){
    try {
        let driver = await new Builder().forBrowser('chrome').build();
        await driver.get('http://youtube.com')
        let foo = await driver.wait( 
                                until.elementLocated(By.id('foo')),
                                30000,
                                'Timed out after 30 seconds',
                                5000);

    }
}