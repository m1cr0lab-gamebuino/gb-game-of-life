/*
 * Scroll Observer
 *
 * adapted from GitHub Pages Theme `Leap Day`:
 * https://github.com/pages-themes/leap-day
 */

var sections = [];
var isGoingToSection = false;

var sectionHeight = function () {
    var total = $(window).height(),
        $section = $('section').css('height', 'auto');

    if ($section.outerHeight(true) < total) {
        var margin = $section.outerHeight(true) - $section.height();
        $section.height(total - margin - 20);
    } else {
        $section.css('height', 'auto');
    }
}

$(window).resize(sectionHeight);

$(function () {
    $("#content h1, #content h2").each(function () {
        var slug = $(this).text().toLowerCase().replace(/ /g, '-').replace(/[^\w-]+/g, '');
        $("nav#toc ul").append("<li class='tag-" + this.nodeName.toLowerCase() + "'><a href='#" + slug + "'>" + $(this).text() + "</a></li>");
        $(this).attr("id", slug);
        sections.push($(this));
        $("nav#toc ul li:first-child a").parent().addClass("active");
    });

    $("nav#toc ul li").on("click", "a", function (event) {
        isGoingToSection = true;
        var position = $($(this).attr("href")).offset().top - 116;
        $("html, body").animate({ scrollTop: position }, 600, 'easeInOutCubic', function() { isGoingToSection = false; });
        $("nav#toc ul li a").parent().removeClass("active");
        $(this).parent().addClass("active");
        event.preventDefault();
    });

    sectionHeight();

    $('img').on('load', sectionHeight);
});

$(window).scroll(function () {
    var n = sections.length;
    if (!isGoingToSection && n > 0) {
        var atBottom = $(this).scrollTop() === $(document).height() - $(window).height();
        var active = $('nav#toc ul li.active');
        var id;
        
        if (atBottom) {
            id = $(sections[n-1]).attr('id');
        } else {
            var scrollTop = $(this).scrollTop() + ($(window).height() / 2);
            var section;
            for (var i in sections) {
                section = sections[i];
                if (scrollTop > $(section).offset().top) {
                    id = section.attr('id');
                }
            }
        }

        var target = $('nav#toc ul li a[href="#' + id + '"]').first().parent();
        if (target != active) {
            active.removeClass('active');
            target.addClass('active');
        }
    }
});