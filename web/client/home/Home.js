
Template.Home.onCreated(function() {
  var self = this;
  self.autorun(function() {
      self.subscribe('alerts')
  })
});

Template.Perifericos.helpers({
    settings: () => {
        return {
            collection: Alerts.find({}),
            fields: [
                { key: 'macAddress', label: 'macAddress', headerClass: 'col-lg-2 col-xl-2' , cellClass: 'col-lg-2 col-xl-2' },
                { key: 'sensorType', label: 'Sensor', headerClass: 'col-lg-1 col-xl-1' , cellClass: 'col-lg-1 col-xl-1' },
                { key: 'value', label: 'Valor aferido', headerClass: 'col-lg-1 col-xl-1' , cellClass: 'col-lg-1 col-xl-1' },
                { key: 'measuredAt', label: 'Data de aferição', headerClass: 'col-lg-2 col-xl-2' , cellClass: 'col-lg-2 col-xl-2' },
                { key: 'createdAt', label: 'Data de postagem', headerClass: 'col-lg-2 col-xl-2' , cellClass: 'col-lg-2 col-xl-2' },
                { key: 'updatedAt', label: 'Data de update', headerClass: 'col-lg-2 col-xl-2' , cellClass: 'col-lg-2 col-xl-2' },
                { key: 'message', label: 'Observações', headerClass: 'col-lg-2 col-xl-2' , cellClass: 'col-lg-2 col-xl-2' },
            ],
        };
    }
});
Template.Alertas.helpers({
  alerts() {
    var alertas = Alerts.find({}).fetch();
    return alertas;      
  },

  alertLevel() {
    console.log(this);
    if( this.value == 0 && this.message!="" ){
      return "alert-danger";
    }
    if( this.value == 0){
      return "alert-warning";
    }
    return false;
  }

});

Template.Alertas.events({
  'click .btn'(event, instance) {
    console.log("click", Template.instance());
    
    $(".reactive-table-input").val(this.macAddress).trigger('submit');
    // increment the counter when button is clicked
    // instance.counter.set(instance.counter.get() + 1);
  },
});
