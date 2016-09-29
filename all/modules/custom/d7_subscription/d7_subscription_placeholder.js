/**
 * Support placeholder changes.
 */
(function ($) {

    /**
     * Register custom state change: placeholder.
     */
    $(document).bind('state:placeholder', function (e) {

        var placeholder = $(e.target).attr('placeholder').replace(/\*+$/, '');

        if (e.trigger) {
            if (e.value) {
                $(e.target).attr('placeholder', placeholder.concat('*'));
            }
            else {
                $(e.target).attr('placeholder', placeholder);
            }
        }
    });
})(jQuery);
