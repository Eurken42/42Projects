$(document).ready(function(){
    $('#action_menu_btn').click(function(){
        $('.action_menu').toggle();
    });
        });

        $(document).ready(function(){
            $("#toggle-chat-btn").click(function(){
                $("#chat-column").toggle();

                if ($("#chat-column").is(":visible")) {
                    $("#main-content").css('width', '60%'); 
                } else {
                    $("#main-content").css('width', '120%');
                }
            });
        });
        