/**
 * Created by root on 07.10.16.
 */
(function ($) {

    Drupal.behaviors.d7PetsMenuBehavior = {
        attach: function (context, settings) {
            setInterval(function () {
                var ajax = new Drupal.ajax(false, '', {url: 'd7_pets_registration_color'});
                ajax.eventResponse(ajax, {});
            }, 3000);
        }
    };
    Drupal.ajax.prototype.commands.change_color = function (ajax, response, status) {
        console.log("1");
        $('div.tabs ul.primary li a').css({'background-color': response.color});
    }
})(jQuery);
