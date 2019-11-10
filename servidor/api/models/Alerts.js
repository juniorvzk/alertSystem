/**
 * Alerts.js
 *
 * @description :: A model definition represents a database table/collection.
 * @docs        :: https://sailsjs.com/docs/concepts/models-and-orm/models
 */

module.exports = {

  tableName: "alerts",
  attributes: {
    sensorType:{
      type: 'string',
      columnName: 'sensorType'
    },
    value:{
      type: 'string',
      columnName: 'value'
    },
    measuredAt:{
      type: 'string',
      columnName: 'measuredAt'
    },
    message:{
      type: 'string',
      columnName: 'message',
      required: false
    }
  },
};

