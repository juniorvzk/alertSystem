/**
 * AlertsController
 *
 * @description :: Server-side actions for handling incoming requests.
 * @help        :: See https://sailsjs.com/docs/concepts/actions
 */

module.exports = {
    async postAlert(req, res) {
        console.log("body: ", req.body );
        // console.log("postAlert\ndata: ", req.data );
        // console.log("postAlert\nquery: ", req.query );
        // console.log("postAlert\ntext: ", req.query );
        var item = await Alerts.create( req.body ).fetch();
        return res.send(item);
        // return res.send({status: 200, item});
    },

    async getAlerts(req, res) {
        console.log("getAlerts");
        var items = await Alerts.find().sort('createdAt DESC');
        return res.send( items );

    }

};

