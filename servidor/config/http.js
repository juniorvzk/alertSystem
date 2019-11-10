/**
 * HTTP Server Settings
 * (sails.config.http)
 *
 * Configuration for the underlying HTTP server in Sails.
 * (for additional recommended settings, see `config/env/production.js`)
 *
 * For more information on configuration, check out:
 * https://sailsjs.com/config/http
 */

module.exports.http = {

  /****************************************************************************
  *                                                                           *
  * Sails/Express middleware to run for every HTTP request.                   *
  * (Only applies to HTTP requests -- not virtual WebSocket requests.)        *
  *                                                                           *
  * https://sailsjs.com/documentation/concepts/middleware                     *
  *                                                                           *
  ****************************************************************************/

  middleware: {

    /***************************************************************************
    *                                                                          *
    * The order in which middleware should be run for HTTP requests.           *
    * (This Sails app's routes are handled by the "router" middleware below.)  *
    *                                                                          *
    ***************************************************************************/
  //  bodyParser: (function() {
  //    // Initialize a skipper instance with the default options.
  //    var skipper = require('skipper')();
  //    // Create and return the middleware function.
  //    return function(req, res, next) {
  //      // If we see the route we want skipped, just continue.
  //      if (req.url === '/dont-parse-me') {
  //        return next();
  //      }
  //      // Otherwise use Skipper to parse the body.
  //      return skipper(req, res, next);
  //    };
  //  })(),
  
  // 'bodyParserText',
  order: [
    'cookieParser',
    'session',
    'bodyParser',
    'compress',
    'poweredBy',
    'router',
    'www',
    'favicon',
  ],
  
  /***************************************************************************
   *                                                                          *
   * The body parser that will handle incoming multipart HTTP requests.       *
    *                                                                          *
    * https://sailsjs.com/config/http#?customizing-the-body-parser             *
    *                                                                          *
    ***************************************************************************/
   
   bodyParser: (function _configureBodyParser(){
    // bodyParser: function(req, res, next) {
     console.log("bodyParser");
     var skipper = require('skipper');
       var middlewareFn = skipper({ strict: true });
       return middlewareFn;
    // },
     })(),

    // bodyParser: function(req, res, next) {
    //   var skipper = require('skipper')();
    //   var rawParser = require("body-parser").raw({type: "*/*"});
    //   console.log(rawParser);
    //   // Create and return the middleware function
    //   return function(req, res, next) {
    //     sails.log.debug(req.headers);
    //     if (req.headers && req.headers['stripe-signature']) {
    //       sails.log.info('request using raw parser middleware');
    //       return rawParser(req, res, next);
    //     }
    //     // Otherwise use Skipper to parse the body
    //     sails.log.info('request using skipper middleware');
    //     return skipper(req, res, next);
    //   };
    // },

  },

};
