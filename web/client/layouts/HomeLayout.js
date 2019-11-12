
Template.HomeLayout.onCreated(function() {
    var self = this;
    this.isNavOpen = new ReactiveVar( true );
    self.autorun(function() {
        self.subscribe('occurrences')
    })
});

Template.HomeLayout.helpers({
    listItems: () => {
        links = [
            {
                path:"/",
                label:"Início",
                icon: "fa fa-home"
            },
            {
                path:"/maps",
                label:"Mapas",
                icon: "fa fa-map"
            },
            {
                path:"/occurrences",
                label:"Ocorrências",
                icon: "fa fa-list"
            },
            {
                path:"/reports",
                label:"Relatorios",
                icon: "fa fa-files-o"
            },
            {
                path:"/people",
                label:"Pessoas",
                icon: "fa fa-users"
            }
        ]
        return links
    },
    isSidenavOpen: () => {
        return Template.instance().isNavOpen.get();
    }

});

Template.HomeLayout.events({
    'click .toogle': function(event, template) {
        nav1 = $(".sidenav").toggleClass("sidenav-open");
        nav2 = $(".sidenav").toggleClass("open");
        nav2 = $(".center-nav").toggleClass("expand");
        bar = $(".sidebar").toggleClass("open");
        open = template.isNavOpen.get();
        console.log(nav1);
        console.log(nav2);
        console.log(bar);
        console.log(open);
        template.isNavOpen.set( !open );
    },
    'click #sidebar li': function(event, template) {
        // console.log(this.router);
        FlowRouter.go(this.path)

    }

});
