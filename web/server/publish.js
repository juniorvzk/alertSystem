Meteor.publish('alerts', function(){
    return Alerts.find({});
});