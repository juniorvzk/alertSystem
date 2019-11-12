FlowRouter.route('/',{
    name: 'home',
    action() {
        GAnalytics.pageview();
        BlazeLayout.render('HomeLayout', { main: 'Home'});
        
    }
});