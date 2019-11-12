
Alerts = new Mongo.Collection('alerts',{idGeneration: 'MONGO'});

Alerts.allow({
    insert: function(userId, doc) {
        return !!userId;
    }
});

Alerts.attachSchema( new SimpleSchema({
    macAddress: {
        type: String,
        label: 'macAddress'
    },
    sensorType: {
        type: String,
        label: 'Sensor'
    },
    value:{
        type: Number,
        label: 'Valor aferido'
    },
    measuredAt:{
        type: String,
        label: 'Data de afericao'
    },
    createdAt:{
        type: Date,
        label: 'Data de postagem'
    },
    updatedAt: {
        type: Date,
        label: 'Data de update'
    }
}) );
