/**
 * jQuery Wheel Color Picker v3.0.3
 * 
 * http://www.jar2.net/projects/jquery-wheelcolorpicker
 * 
 * Author : Fajar Chandra
 * Date   : 2017.09.03
 * 
 * Copyright © 2011-2017 Fajar Chandra. All rights reserved.
 * Released under MIT License.
 * http://www.opensource.org/licenses/mit-license.php
 */
!function(a){a.fn.wheelColorPicker=function(){var c=this;if(arguments.length>0)var d=[].shift,e=d.apply(arguments),f="string"==typeof e?e.charAt(0).toUpperCase()+e.slice(1):e;else var e=void 0,f=void 0;var g=arguments;return this.each(function(){var d=a(this).data("jQWCP.instance");if(void 0==d||null==d){var h={};"object"==typeof e&&(h=e),d=new b.ColorPicker(this,h),a(this).data("jQWCP.instance",d)}if(void 0===e||"object"==typeof e);else if("function"==typeof d[e]){var i=d[e].apply(d,g);if(i!==d)return c=i,!1}else if("function"==typeof d["set"+f]&&g.length>0){var i=d["set"+f].apply(d,g);if(i!==d)return c=i,!1}else if("function"==typeof d["get"+f]){var i=d["get"+f].apply(d,g);if(i!==d)return c=i,!1}else if(void 0!==d.options[e]&&g.length>0)d.options[e]=g[0];else{if(void 0!==d.options[e])return c=d.options[e],!1;a.error("Method/option named "+e+" does not exist on jQuery.wheelColorPicker")}}),c};var b=a.fn.wheelColorPicker;b.defaults={format:"hex",preview:!1,live:!0,userinput:!0,validate:!0,autoResize:!0,autoFormat:!0,preserveWheel:null,cssClass:"",layout:"popup",animDuration:200,quality:1,sliders:null,rounding:2,mobile:!0,mobileWidth:480,hideKeyboard:!1,htmlOptions:!0,snap:!1,snapTolerance:.05},b.BUG_RELATIVE_PAGE_ORIGIN=!1,b.ORIGIN={left:0,top:0},b.colorToStr=function(a,b){var c="";switch(b){case"css":c="#";case"hex":var d=Math.round(255*a.r).toString(16);1==d.length&&(d="0"+d);var e=Math.round(255*a.g).toString(16);1==e.length&&(e="0"+e);var f=Math.round(255*a.b).toString(16);1==f.length&&(f="0"+f),c+=d+e+f;break;case"cssa":c="#";case"hexa":var d=Math.round(255*a.r).toString(16);1==d.length&&(d="0"+d);var e=Math.round(255*a.g).toString(16);1==e.length&&(e="0"+e);var f=Math.round(255*a.b).toString(16);1==f.length&&(f="0"+f);var g=Math.round(255*a.a).toString(16);1==g.length&&(g="0"+g),c+=d+e+f+g;break;case"rgb":c="rgb("+Math.round(255*a.r)+","+Math.round(255*a.g)+","+Math.round(255*a.b)+")";break;case"rgb%":c="rgb("+100*a.r+"%,"+100*a.g+"%,"+100*a.b+"%)";break;case"rgba":c="rgba("+Math.round(255*a.r)+","+Math.round(255*a.g)+","+Math.round(255*a.b)+","+a.a+")";break;case"rgba%":c="rgba("+100*a.r+"%,"+100*a.g+"%,"+100*a.b+"%,"+100*a.a+"%)";break;case"hsv":c="hsv("+360*a.h+","+a.s+","+a.v+")";break;case"hsv%":c="hsv("+100*a.h+"%,"+100*a.s+"%,"+100*a.v+"%)";break;case"hsva":c="hsva("+360*a.h+","+a.s+","+a.v+","+a.a+")";break;case"hsva%":c="hsva("+100*a.h+"%,"+100*a.s+"%,"+100*a.v+"%,"+100*a.a+"%)";break;case"hsb":c="hsb("+a.h+","+a.s+","+a.v+")";break;case"hsb%":c="hsb("+100*a.h+"%,"+100*a.s+"%,"+100*a.v+"%)";break;case"hsba":c="hsba("+a.h+","+a.s+","+a.v+","+a.a+")";break;case"hsba%":c="hsba("+100*a.h+"%,"+100*a.s+"%,"+100*a.v+"%,"+100*a.a+"%)"}return c},b.strToColor=function(a){var c,d,b={a:1};if(null!=a.match(/^#[0-9a-f]{3}$/i)||a.match(/^#[0-9a-f]{4}$/i)){if(isNaN(b.r=17*parseInt(a.substr(1,1),16)/255))return!1;if(isNaN(b.g=17*parseInt(a.substr(2,1),16)/255))return!1;if(isNaN(b.b=17*parseInt(a.substr(3,1),16)/255))return!1;if(5==a.length&&isNaN(b.a=17*parseInt(a.substr(4,1),16)/255))return!1}else if(null!=a.match(/^[0-9a-f]{3}$/i)||null!=a.match(/^[0-9a-f]{4}$/i)){if(isNaN(b.r=17*parseInt(a.substr(0,1),16)/255))return!1;if(isNaN(b.g=17*parseInt(a.substr(1,1),16)/255))return!1;if(isNaN(b.b=17*parseInt(a.substr(2,1),16)/255))return!1;if(4==a.length&&isNaN(b.a=17*parseInt(a.substr(3,1),16)/255))return!1}else if(null!=a.match(/^#[0-9a-f]{6}$/i)||null!=a.match(/^#[0-9a-f]{8}$/i)){if(isNaN(b.r=parseInt(a.substr(1,2),16)/255))return!1;if(isNaN(b.g=parseInt(a.substr(3,2),16)/255))return!1;if(isNaN(b.b=parseInt(a.substr(5,2),16)/255))return!1;if(9==a.length&&isNaN(b.a=parseInt(a.substr(7,2),16)/255))return!1}else if(null!=a.match(/^[0-9a-f]{6}$/i)||null!=a.match(/^[0-9a-f]{8}$/i)){if(isNaN(b.r=parseInt(a.substr(0,2),16)/255))return!1;if(isNaN(b.g=parseInt(a.substr(2,2),16)/255))return!1;if(isNaN(b.b=parseInt(a.substr(4,2),16)/255))return!1;if(8==a.length&&isNaN(b.a=parseInt(a.substr(6,2),16)/255))return!1}else if(null!=a.match(/^rgba\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i)||null!=a.match(/^rgb\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i)){if(d=null!=a.match(/a/i),c=a.substring(a.indexOf("(")+1,a.indexOf(",")),"%"==c.charAt(c.length-1)){if(isNaN(b.r=parseFloat(c)/100))return!1}else if(isNaN(b.r=parseInt(c)/255))return!1;if(c=a.substring(a.indexOf(",")+1,a.indexOf(",",a.indexOf(",")+1)),"%"==c.charAt(c.length-1)){if(isNaN(b.g=parseFloat(c)/100))return!1}else if(isNaN(b.g=parseInt(c)/255))return!1;if(c=d?a.substring(a.indexOf(",",a.indexOf(",")+1)+1,a.lastIndexOf(",")):a.substring(a.lastIndexOf(",")+1,a.lastIndexOf(")")),"%"==c.charAt(c.length-1)){if(isNaN(b.b=parseFloat(c)/100))return!1}else if(isNaN(b.b=parseInt(c)/255))return!1;if(d)if(c=a.substring(a.lastIndexOf(",")+1,a.lastIndexOf(")")),"%"==c.charAt(c.length-1)){if(isNaN(b.a=parseFloat(c)/100))return!1}else if(isNaN(b.a=parseFloat(c)))return!1}else{if(null==a.match(/^hsva\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i)&&null==a.match(/^hsv\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i)&&null==a.match(/^hsba\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i)&&null==a.match(/^hsb\s*\(\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*,\s*([0-9\.]+%|[01]?\.?[0-9]*)\s*\)$/i))return!1;if(d=null!=a.match(/a/i),c=a.substring(a.indexOf("(")+1,a.indexOf(",")),"%"==c.charAt(c.length-1)){if(isNaN(b.h=parseFloat(c)/100))return!1}else if(isNaN(b.h=parseFloat(c)/360))return!1;if(c=a.substring(a.indexOf(",")+1,a.indexOf(",",a.indexOf(",")+1)),"%"==c.charAt(c.length-1)){if(isNaN(b.s=parseFloat(c)/100))return!1}else if(isNaN(b.s=parseFloat(c)))return!1;if(c=d?a.substring(a.indexOf(",",a.indexOf(",")+1)+1,a.lastIndexOf(",")):a.substring(a.lastIndexOf(",")+1,a.lastIndexOf(")")),"%"==c.charAt(c.length-1)){if(isNaN(b.v=parseFloat(c)/100))return!1}else if(isNaN(b.v=parseFloat(c)))return!1;if(d)if(c=a.substring(a.lastIndexOf(",")+1,a.lastIndexOf(")")),"%"==c.charAt(c.length-1)){if(isNaN(b.a=parseFloat(c)/100))return!1}else if(isNaN(b.a=parseFloat(c)))return!1}return b},b.hsvToRgb=function(a,b,c){var d=a<=1/6||a>=5/6?1:a<1/3?1-6*(a-1/6):a>4/6?6*(a-4/6):0,e=a>=1/6&&a<=.5?1:a<1/6?6*a:a<4/6?1-6*(a-.5):0,f=a>=.5&&a<=5/6?1:a>2/6&&a<.5?6*(a-2/6):a>5/6?1-6*(a-5/6):0,g=(d+(1-d)*(1-b))*c,h=(e+(1-e)*(1-b))*c,i=(f+(1-f)*(1-b))*c;return{r:g,g:h,b:i}},b.rgbToHsv=function(a,b,c){var d,e,f,g=Math.max(a,b,c),h=Math.min(a,b,c),i=g-h;return e=0!=g?i/g:0,d=0==i?0:a==g?(6+(b-c)/i)%6:b==g?2+(c-a)/i:c==g?4+(a-b)/i:0,d/=6,f=g,{h:d,s:e,v:f}},b.ColorPicker=function(c,d){this.input=c,this.color={h:0,s:0,v:1,r:1,g:1,b:1,a:1},this.setValue(this.input.value),this.options=a.extend(!0,{},b.defaults),this.setOptions(d),null==this.options.sliders&&(this.options.sliders="wvp"+(this.options.format.indexOf("a")>=0?"a":"")),this.init()},b.ColorPicker.widget=null,b.ColorPicker.overlay=null,b.ColorPicker.init=function(){if(1!=b.ColorPicker.init.hasInit){b.ColorPicker.init.hasInit=!0;var c=a('<div class="jQWCP-overlay" style="display: none;"></div>');c.on("click",b.Handler.overlay_click),b.ColorPicker.overlay=c.get(0),a("body").append(c);var d=b.ColorPicker.getWheelDataUrl(200);a("head").append('<style type="text/css">.jQWCP-wWheel {background: url('+d+") no-repeat center center;}</style>"),a("html").on("mouseup.wheelColorPicker",b.Handler.html_mouseup),a("html").on("touchend.wheelColorPicker",b.Handler.html_mouseup),a("html").on("mousemove.wheelColorPicker",b.Handler.html_mousemove),a("html").on("touchmove.wheelColorPicker",b.Handler.html_mousemove),a(window).on("resize.wheelColorPicker",b.Handler.window_resize)}},b.ColorPicker.createWidget=function(){var c=a("<div class='jQWCP-wWidget'><div class='jQWCP-wWheel'><div class='jQWCP-wWheelOverlay'></div><span class='jQWCP-wWheelCursor'></span></div><div class='jQWCP-wHue jQWCP-slider-wrapper'><canvas class='jQWCP-wHueSlider jQWCP-slider' width='1' height='50' title='Hue'></canvas><span class='jQWCP-wHueCursor jQWCP-scursor'></span></div><div class='jQWCP-wSat jQWCP-slider-wrapper'><canvas class='jQWCP-wSatSlider jQWCP-slider' width='1' height='50' title='Saturation'></canvas><span class='jQWCP-wSatCursor jQWCP-scursor'></span></div><div class='jQWCP-wVal jQWCP-slider-wrapper'><canvas class='jQWCP-wValSlider jQWCP-slider' width='1' height='50' title='Value'></canvas><span class='jQWCP-wValCursor jQWCP-scursor'></span></div><div class='jQWCP-wRed jQWCP-slider-wrapper'><canvas class='jQWCP-wRedSlider jQWCP-slider' width='1' height='50' title='Red'></canvas><span class='jQWCP-wRedCursor jQWCP-scursor'></span></div><div class='jQWCP-wGreen jQWCP-slider-wrapper'><canvas class='jQWCP-wGreenSlider jQWCP-slider' width='1' height='50' title='Green'></canvas><span class='jQWCP-wGreenCursor jQWCP-scursor'></span></div><div class='jQWCP-wBlue jQWCP-slider-wrapper'><canvas class='jQWCP-wBlueSlider jQWCP-slider' width='1' height='50' title='Blue'></canvas><span class='jQWCP-wBlueCursor jQWCP-scursor'></span></div><div class='jQWCP-wAlpha jQWCP-slider-wrapper'><canvas class='jQWCP-wAlphaSlider jQWCP-slider' width='1' height='50' title='Alpha'></canvas><span class='jQWCP-wAlphaCursor jQWCP-scursor'></span></div><div class='jQWCP-wPreview'><canvas class='jQWCP-wPreviewBox' width='1' height='1' title='Selected Color'></canvas></div></div>");return c.find(".jQWCP-wWheel, .jQWCP-slider-wrapper, .jQWCP-scursor, .jQWCP-slider").attr("unselectable","on").css("-moz-user-select","none").css("-webkit-user-select","none").css("user-select","none").css("-webkit-touch-callout","none"),c.on("contextmenu.wheelColorPicker",function(){return!1}),c.on("mousedown.wheelColorPicker",".jQWCP-wWheel",b.Handler.wheel_mousedown),c.on("touchstart.wheelColorPicker",".jQWCP-wWheel",b.Handler.wheel_mousedown),c.on("mousedown.wheelColorPicker",".jQWCP-wWheelCursor",b.Handler.wheelCursor_mousedown),c.on("touchstart.wheelColorPicker",".jQWCP-wWheelCursor",b.Handler.wheelCursor_mousedown),c.on("mousedown.wheelColorPicker",".jQWCP-slider",b.Handler.slider_mousedown),c.on("touchstart.wheelColorPicker",".jQWCP-slider",b.Handler.slider_mousedown),c.on("mousedown.wheelColorPicker",".jQWCP-scursor",b.Handler.sliderCursor_mousedown),c.on("touchstart.wheelColorPicker",".jQWCP-scursor",b.Handler.sliderCursor_mousedown),c.get(0)},b.ColorPicker.getWheelDataUrl=function(a){var b=a/2,c=b,d=document.createElement("canvas");d.width=a,d.height=a;for(var e=d.getContext("2d"),f=0;f<a;f++)for(var g=0;g<a;g++){var h=Math.sqrt(Math.pow(g-c,2)+Math.pow(f-c,2));if(!(h>b+2)){var i=((g-c==0?f<c?90:270:Math.atan((c-f)/(g-c))/Math.PI*180)+(g<c?180:0)+360)%360,j=h/b,l=(Math.abs(i+360)+60)%360<120?1:i>240?(120-Math.abs(i-360))/60:i<120?(120-i)/60:0,m=Math.abs(i-120)<60?1:Math.abs(i-120)<120?(120-Math.abs(i-120))/60:0,n=Math.abs(i-240)<60?1:Math.abs(i-240)<120?(120-Math.abs(i-240))/60:0,o=Math.round(255*(l+(1-l)*(1-j))),p=Math.round(255*(m+(1-m)*(1-j))),q=Math.round(255*(n+(1-n)*(1-j)));e.fillStyle="rgb("+o+","+p+","+q+")",e.fillRect(g,f,1,1)}}return d.toDataURL()},b.ColorPicker.prototype.options=null,b.ColorPicker.prototype.input=null,b.ColorPicker.prototype.widget=null,b.ColorPicker.prototype.color=null,b.ColorPicker.prototype.lastValue=null,b.ColorPicker.prototype.setOptions=function(c){if(c=a.extend(!0,{},c),this.options.htmlOptions)for(var d in b.defaults)this.input.hasAttribute("data-wcp-"+d)&&void 0===c[d]&&(c[d]=this.input.getAttribute("data-wcp-"+d),"true"==c[d]?c[d]=!0:"false"==c[d]&&(c[d]=!1));for(var d in c)if(void 0!==this.options[d]){var e=d.charAt(0).toUpperCase()+d.slice(1);"function"==typeof this["set"+e]?this["set"+e](c[d]):this.options[d]=c[d]}return this},b.ColorPicker.prototype.init=function(){if(b.ColorPicker.init(),1!=this.hasInit){this.hasInit=!0;var d=a(this.input),e=null;"block"==this.options.layout?(this.widget=b.ColorPicker.createWidget(),e=a(this.widget),e.data("jQWCP.instance",this),e.insertAfter(this.input),"inline"==d.css("display")?e.css("display","inline-block"):e.css("display",d.css("display")),e.append(this.input),d.hide(),void 0!=d.attr("tabindex")?e.attr("tabindex",d.attr("tabindex")):e.attr("tabindex",0),this.refreshWidget(),this.redrawSliders(!0),this.updateSliders(),e.on("focus.wheelColorPicker",b.Handler.widget_focus_block),e.on("blur.wheelColorPicker",b.Handler.widget_blur_block)):(null==b.ColorPicker.widget&&(b.ColorPicker.widget=b.ColorPicker.createWidget(),e=a(b.ColorPicker.widget),e.hide(),a("body").append(e),e.on("mousedown.wheelColorPicker",b.Handler.widget_mousedown_popup)),this.widget=b.ColorPicker.widget,d.on("focus.wheelColorPicker",b.Handler.input_focus_popup),d.on("blur.wheelColorPicker",b.Handler.input_blur_popup)),d.on("keyup.wheelColorPicker",b.Handler.input_keyup),d.on("change.wheelColorPicker",b.Handler.input_change),"object"==typeof this.options.color?(this.setColor(this.options.color),this.options.color=void 0):"string"==typeof this.options.color&&(this.setValue(this.options.color),this.options.color=void 0),this.options.userinput?d.removeAttr("readonly"):d.attr("readonly",!0)}},b.ColorPicker.prototype.destroy=function(){var b=a(this.widget),c=a(this.input);"block"==this.options.layout&&(b.before(this.input),b.remove(),c.show()),c.off("focus.wheelColorPicker"),c.off("blur.wheelColorPicker"),c.off("keyup.wheelColorPicker"),c.off("change.wheelColorPicker"),c.data("jQWCP.instance",null),delete this},b.ColorPicker.prototype.refreshWidget=function(){var b=a(this.widget),c=this.options,d=!1;b.attr("class","jQWCP-wWidget"),"block"==c.layout&&b.addClass("jQWCP-block"),b.addClass(c.cssClass),window.innerWidth<=c.mobileWidth&&"block"!=c.layout&&c.mobile&&(d=!0,b.addClass("jQWCP-mobile")),b.find(".jQWCP-wWheel, .jQWCP-slider-wrapper, .jQWCP-wPreview").hide().addClass("hidden");for(var e in c.sliders){var f=null;switch(this.options.sliders[e]){case"w":f=b.find(".jQWCP-wWheel");break;case"h":f=b.find(".jQWCP-wHue");break;case"s":f=b.find(".jQWCP-wSat");break;case"v":f=b.find(".jQWCP-wVal");break;case"r":f=b.find(".jQWCP-wRed");break;case"g":f=b.find(".jQWCP-wGreen");break;case"b":f=b.find(".jQWCP-wBlue");break;case"a":f=b.find(".jQWCP-wAlpha");break;case"p":f=b.find(".jQWCP-wPreview")}null!=f&&(f.appendTo(this.widget),f.show().removeClass("hidden"))}var g=50*c.quality;b.find(".jQWCP-slider").attr("height",g);var h=b.find(".jQWCP-wWheel, .jQWCP-slider-wrapper, .jQWCP-wPreview").not(".hidden");if(c.autoResize&&!d){var i=0;h.css({width:"",height:""}),h.each(function(b,c){var d=a(c);i+=parseFloat(d.css("margin-left").replace("px",""))+parseFloat(d.css("margin-right").replace("px",""))+d.outerWidth()}),b.css({width:i+"px"})}else{b.css({width:""});var j=b.find(".jQWCP-wWheel").not(".hidden"),k=b.find(".jQWCP-slider-wrapper, .jQWCP-wPreview").not(".hidden");if(j.css({height:b.height()+"px",width:b.height()}),j.length>0)var l=b.width()-j.outerWidth()-parseFloat(j.css("margin-left").replace("px",""))-parseFloat(j.css("margin-right").replace("px",""));else var l=b.width();if(k.length>0){var m=parseFloat(k.css("margin-left").replace("px",""))+parseFloat(k.css("margin-right").replace("px",""));k.css({height:b.height()+"px",width:(l-(k.length-1)*m)/k.length+"px"})}}return this},b.ColorPicker.prototype.redrawSliders=function(b){if(null==this.widget)return this;var c=a(this.widget);if("string"==typeof arguments[0]&&(b=arguments[1]),this!=c.data("jQWCP.instance"))return this;var d=this.options,e=this.color,f=1,g=50*d.quality,h=1,i=0,j=0,k=0,l=0,m=0,n=1;d.live&&(h=e.a,i=Math.round(255*e.r),j=Math.round(255*e.g),k=Math.round(255*e.b),l=e.h,m=e.s,n=e.v);var o=c.find(".jQWCP-wPreviewBox");if(!o.hasClass("hidden")){var p=o.get(0).getContext("2d");p.fillStyle="rgba("+i+","+j+","+k+","+h+")",p.clearRect(0,0,1,1),p.fillRect(0,0,1,1)}if(!this.options.live&&!b)return this;var q=c.find(".jQWCP-wAlphaSlider");if(!q.hasClass("hidden")||b){var r=q.get(0).getContext("2d"),s=r.createLinearGradient(0,0,0,g);s.addColorStop(0,"rgba("+i+","+j+","+k+",1)"),s.addColorStop(1,"rgba("+i+","+j+","+k+",0)"),r.fillStyle=s,r.clearRect(0,0,f,g),r.fillRect(0,0,f,g)}var t=c.find(".jQWCP-wRedSlider");if(!t.hasClass("hidden")||b){var u=t.get(0).getContext("2d"),v=u.createLinearGradient(0,0,0,g);v.addColorStop(0,"rgb(255,"+j+","+k+")"),v.addColorStop(1,"rgb(0,"+j+","+k+")"),u.fillStyle=v,u.fillRect(0,0,f,g)}var w=c.find(".jQWCP-wGreenSlider");if(!w.hasClass("hidden")||b){var x=w.get(0).getContext("2d"),y=x.createLinearGradient(0,0,0,g);y.addColorStop(0,"rgb("+i+",255,"+k+")"),y.addColorStop(1,"rgb("+i+",0,"+k+")"),x.fillStyle=y,x.fillRect(0,0,f,g)}var z=c.find(".jQWCP-wBlueSlider");if(!z.hasClass("hidden")||b){var A=z.get(0).getContext("2d"),B=A.createLinearGradient(0,0,0,g);B.addColorStop(0,"rgb("+i+","+j+",255)"),B.addColorStop(1,"rgb("+i+","+j+",0)"),A.fillStyle=B,A.fillRect(0,0,f,g)}var C=c.find(".jQWCP-wHueSlider");if(!C.hasClass("hidden")||b){var D=C.get(0).getContext("2d"),E=D.createLinearGradient(0,0,0,g);E.addColorStop(0,"#f00"),E.addColorStop(.166666667,"#ff0"),E.addColorStop(.333333333,"#0f0"),E.addColorStop(.5,"#0ff"),E.addColorStop(.666666667,"#00f"),E.addColorStop(.833333333,"#f0f"),E.addColorStop(1,"#f00"),D.fillStyle=E,D.fillRect(0,0,f,g)}var F=c.find(".jQWCP-wSatSlider");if(!F.hasClass("hidden")||b){var G=a.fn.wheelColorPicker.hsvToRgb(l,1,n);G.r=Math.round(255*G.r),G.g=Math.round(255*G.g),G.b=Math.round(255*G.b);var H=F.get(0).getContext("2d"),I=H.createLinearGradient(0,0,0,g);I.addColorStop(0,"rgb("+G.r+","+G.g+","+G.b+")"),I.addColorStop(1,"rgb("+Math.round(255*n)+","+Math.round(255*n)+","+Math.round(255*n)+")"),H.fillStyle=I,H.fillRect(0,0,f,g)}var J=c.find(".jQWCP-wValSlider");if(!J.hasClass("hidden")||b){var K=a.fn.wheelColorPicker.hsvToRgb(l,m,1);K.r=Math.round(255*K.r),K.g=Math.round(255*K.g),K.b=Math.round(255*K.b);var L=J.get(0).getContext("2d"),M=L.createLinearGradient(0,0,0,g);M.addColorStop(0,"rgb("+K.r+","+K.g+","+K.b+")"),M.addColorStop(1,"#000"),L.fillStyle=M,L.fillRect(0,0,f,g)}return this},b.ColorPicker.prototype.updateSliders=function(){if(null==this.widget)return this;var b=a(this.widget),c=this.color;if(this!=b.data("jQWCP.instance"))return this;var d=b.find(".jQWCP-wWheel");if(!d.hasClass("hidden")){var e=b.find(".jQWCP-wWheelCursor"),f=b.find(".jQWCP-wWheelOverlay"),g=Math.cos(2*Math.PI*c.h)*c.s,h=Math.sin(2*Math.PI*c.h)*c.s,i=d.width()/2,j=d.height()/2;e.css("left",i+g*d.width()/2+"px"),e.css("top",j-h*d.height()/2+"px"),1==this.options.preserveWheel||null==this.options.preserveWheel&&0==this.options.live?f.css("opacity",0):f.css("opacity",1-(c.v<.2?.2:c.v))}var k=b.find(".jQWCP-wHueSlider");if(!k.hasClass("hidden")){var l=b.find(".jQWCP-wHueCursor");l.css("top",c.h*k.height()+"px")}var m=b.find(".jQWCP-wSatSlider");if(!m.hasClass("hidden")){var n=b.find(".jQWCP-wSatCursor");n.css("top",(1-c.s)*m.height()+"px")}var o=b.find(".jQWCP-wValSlider");if(!o.hasClass("hidden")){var p=b.find(".jQWCP-wValCursor");p.css("top",(1-c.v)*o.height()+"px")}var q=b.find(".jQWCP-wRedSlider");if(!q.hasClass("hidden")){var r=b.find(".jQWCP-wRedCursor");r.css("top",(1-c.r)*q.height()+"px")}var s=b.find(".jQWCP-wGreenSlider");if(!s.hasClass("hidden")){var t=b.find(".jQWCP-wGreenCursor");t.css("top",(1-c.g)*s.height()+"px")}var u=b.find(".jQWCP-wBlueSlider");if(!u.hasClass("hidden")){var v=b.find(".jQWCP-wBlueCursor");v.css("top",(1-c.b)*u.height()+"px")}var w=b.find(".jQWCP-wAlphaSlider");if(!w.hasClass("hidden")){var x=b.find(".jQWCP-wAlphaCursor");x.css("top",(1-c.a)*w.height()+"px")}return this},b.ColorPicker.prototype.updateSelection=function(){return this.redrawSliders(),this.updateSliders(),this},b.ColorPicker.prototype.updateInput=function(){if(null==this.widget)return this;var c=a(this.input);this.input.value!=this.getValue()&&(this.input.value=this.getValue()),this.options.preview&&(c.css("background",b.colorToStr(this.color,"rgba")),this.color.v>.5?c.css("color","black"):c.css("color","white"))},b.ColorPicker.prototype.updateActiveControl=function(c){var d=a(a("body").data("jQWCP.activeControl"));if(0!=d.length){var f=(a(this.input),this.options),g=this.color;if(void 0==c.pageX&&c.originalEvent.touches.length>0&&(c.pageX=c.originalEvent.touches[0].pageX,c.pageY=c.originalEvent.touches[0].pageY),d.hasClass("jQWCP-wWheel")){var h=d.find(".jQWCP-wWheelCursor"),j=(d.find(".jQWCP-wWheelOverlay"),(c.pageX-d.offset().left-d.width()/2)/(d.width()/2)),k=-(c.pageY-d.offset().top-d.height()/2)/(d.height()/2);if(b.BUG_RELATIVE_PAGE_ORIGIN)var j=(c.pageX-(d.get(0).getBoundingClientRect().left-b.ORIGIN.left)-d.width()/2)/(d.width()/2),k=-(c.pageY-(d.get(0).getBoundingClientRect().top-b.ORIGIN.top)-d.height()/2)/(d.height()/2);var l=Math.sqrt(Math.pow(j,2)+Math.pow(k,2));l>1&&(l=1),f.snap&&l<f.snapTolerance&&(l=0);var m=0==j&&0==k?0:Math.atan(k/j)/(2*Math.PI);m<0&&(m+=.5),k<0&&(m+=.5),this.setHsv(m,l,g.v)}else if(d.hasClass("jQWCP-slider-wrapper")){var h=d.find(".jQWCP-scursor"),k=(c.pageY-d.offset().top)/d.height();if(b.BUG_RELATIVE_PAGE_ORIGIN)var k=(c.pageY-(d.get(0).getBoundingClientRect().top-b.ORIGIN.top))/d.height();var n=k<0?0:k>1?1:k;f.snap&&n<f.snapTolerance?n=0:f.snap&&n>1-f.snapTolerance&&(n=1),f.snap&&n>.5-f.snapTolerance&&n<.5+f.snapTolerance&&(n=.5),h.css("top",n*d.height()+"px"),d.hasClass("jQWCP-wRed")&&this.setRgb(1-n,g.g,g.b),d.hasClass("jQWCP-wGreen")&&this.setRgb(g.r,1-n,g.b),d.hasClass("jQWCP-wBlue")&&this.setRgb(g.r,g.g,1-n),d.hasClass("jQWCP-wHue")&&this.setHsv(n,g.s,g.v),d.hasClass("jQWCP-wSat")&&this.setHsv(g.h,1-n,g.v),d.hasClass("jQWCP-wVal")&&this.setHsv(g.h,g.s,1-n),d.hasClass("jQWCP-wAlpha")&&this.setAlpha(1-n)}}},b.ColorPicker.prototype.getColor=function(){return this.color},b.ColorPicker.prototype.getValue=function(a){var c=this.options;return null==a&&(a=c.format),c.rounding>=0&&(this.color.a=Math.round(this.color.a*Math.pow(10,c.rounding))/Math.pow(10,c.rounding)),b.colorToStr(this.color,a)},b.ColorPicker.prototype.setValue=function(a,c){var d=b.strToColor(a);return d?this.setColor(d,c):this},b.ColorPicker.prototype.setColor=function(a,b){return"string"==typeof a?this.setValue(a,b):null!=a.r?this.setRgba(a.r,a.g,a.b,a.a,b):null!=a.h?this.setHsva(a.h,a.s,a.v,a.a,b):null!=a.a?this.setAlpha(a.a,b):this},b.ColorPicker.prototype.setRgba=function(a,c,d,e,f){void 0===f&&(f=!0);var g=this.color;g.r=a,g.g=c,g.b=d,null!=e&&(g.a=e);var h=b.rgbToHsv(a,c,d);return g.h=h.h,g.s=h.s,g.v=h.v,this.updateSliders(),this.redrawSliders(),f&&this.updateInput(),this},b.ColorPicker.prototype.setRgb=function(a,b,c,d){return this.setRgba(a,b,c,null,d)},b.ColorPicker.prototype.setHsva=function(a,c,d,e,f){void 0===f&&(f=!0);var g=this.color;g.h=a,g.s=c,g.v=d,null!=e&&(g.a=e);var h=b.hsvToRgb(a,c,d);return g.r=h.r,g.g=h.g,g.b=h.b,this.updateSliders(),this.redrawSliders(),f&&this.updateInput(),this},b.ColorPicker.prototype.setHsv=function(a,b,c,d){return this.setHsva(a,b,c,null,d)},b.ColorPicker.prototype.setAlpha=function(a,b){return void 0===b&&(b=!0),this.color.a=a,this.updateSliders(),this.redrawSliders(),b&&this.updateInput(),this},b.ColorPicker.prototype.show=function(){var c=this.input,d=a(c),e=a(this.widget),f=this.options;if("popup"==f.layout&&(e.data("jQWCP.instance",this),e.stop(!0,!0),e.css({top:c.getBoundingClientRect().top-b.ORIGIN.top+d.outerHeight()+"px",left:c.getBoundingClientRect().left-b.ORIGIN.left+"px"}),this.refreshWidget(),this.redrawSliders(),this.updateSliders(),this.lastValue=c.value,e.fadeIn(f.animDuration),f.hideKeyboard&&(d.blur(),a(b.ColorPicker.overlay).show()),e.hasClass("jQWCP-mobile"))){var g=a("html").scrollTop(),h=c.getBoundingClientRect().top-b.ORIGIN.top;h<g?a("html").animate({scrollTop:h}):h+d.outerHeight()>g+window.innerHeight-e.outerHeight()&&a("html").animate({scrollTop:h+d.outerHeight()-window.innerHeight+e.outerHeight()})}},b.ColorPicker.prototype.hide=function(){var c=a(this.widget);this==c.data("jQWCP.instance")&&(c.fadeOut(this.options.animDuration),a(b.ColorPicker.overlay).hide())},b.Handler={},b.Handler.input_focus_popup=function(b){var c=a(this).data("jQWCP.instance");c.show(),null==a(this).attr("readonly")&&(a(this).attr("readonly",!0),setTimeout(function(){a(c.input).removeAttr("readonly")}),null!=navigator.userAgent.match(/Android .* Firefox/)&&setTimeout(function(){a(c.input).attr("readonly",!0),a(c.input).one("blur",function(){a(c.input).removeAttr("readonly")})}))},b.Handler.input_blur_popup=function(b){var c=a(this).data("jQWCP.instance");c.options.hideKeyboard||(c.hide(),c.lastValue!=this.value&&a(this).trigger("change"))},b.Handler.input_keyup=function(c){var d=a(this).data("jQWCP.instance"),e=b.strToColor(this.value);e&&d.setColor(e,!1)},b.Handler.input_change=function(c){var d=a(this).data("jQWCP.instance"),e=b.strToColor(this.value);d.options.autoFormat&&e?d.setColor(e,!0):d.options.validate&&!e&&""!=this.value&&(this.value=d.getValue())},b.Handler.widget_focus_block=function(b){var c=a(this).data("jQWCP.instance"),d=a(c.input);c.lastValue=c.input.value,d.triggerHandler("focus")},b.Handler.widget_mousedown_popup=function(b){var c=a(this).data("jQWCP.instance"),d=a(c.input);if(d.off("focus.wheelColorPicker"),d.off("blur.wheelColorPicker"),void 0!=d.data("events"))var e=d.data("events").blur;else var e=void 0;var f={blur:[]};if(void 0!=e)for(var g=0;g<e.length;g++)f.blur.push(e[g]);d.data("jQWCP.suspendedEvents",f)},b.Handler.widget_blur_block=function(b){var c=a(this).data("jQWCP.instance"),d=a(c.input);c.lastValue!=c.input.value&&d.trigger("change"),d.triggerHandler("blur")},b.Handler.wheelCursor_mousedown=function(b){var c=a(this),d=c.closest(".jQWCP-wWidget"),e=d.data("jQWCP.instance"),f=a(e.input);a("body").data("jQWCP.activeControl",c.parent().get(0)),f.trigger("sliderdown")},b.Handler.wheel_mousedown=function(b){var c=a(this),d=c.closest(".jQWCP-wWidget"),e=d.data("jQWCP.instance"),f=a(e.input);a("body").data("jQWCP.activeControl",c.get(0)),f.trigger("sliderdown")},b.Handler.slider_mousedown=function(b){var c=a(this),d=c.closest(".jQWCP-wWidget"),e=d.data("jQWCP.instance"),f=a(e.input);a("body").data("jQWCP.activeControl",c.parent().get(0)),f.trigger("sliderdown")},b.Handler.sliderCursor_mousedown=function(b){var c=a(this),d=c.closest(".jQWCP-wWidget"),e=d.data("jQWCP.instance"),f=a(e.input);a("body").data("jQWCP.activeControl",c.parent().get(0)),f.trigger("sliderdown")},b.Handler.html_mouseup=function(c){var d=a(a("body").data("jQWCP.activeControl"));if(0!=d.length){var e=d.closest(".jQWCP-wWidget"),f=e.data("jQWCP.instance"),g=a(f.input);if("popup"==f.options.layout){f.options.hideKeyboard||g.trigger("focus.jQWCP_DONT_TRIGGER_EVENTS"),g.on("focus.wheelColorPicker",b.Handler.input_focus_popup),g.on("blur.wheelColorPicker",b.Handler.input_blur_popup);var h=g.data("jQWCP.suspendedEvents");if(void 0!=h)for(var i=h.blur,j=0;j<i.length;j++)g.on("blur"+(""==i[j].namespace?"":"."+i[j].namespace),i[j].handler)}0!=d.length&&(void 0!=c.pageX&&f.updateActiveControl(c),a("body").data("jQWCP.activeControl",null),g.trigger("sliderup"))}},b.Handler.html_mousemove=function(b){var c=a(a("body").data("jQWCP.activeControl"));if(0!=c.length){b.preventDefault();var d=c.closest(".jQWCP-wWidget"),e=d.data("jQWCP.instance"),f=a(e.input);return e.updateActiveControl(b),f.trigger("slidermove"),!1}},b.Handler.window_resize=function(b){var c=a("body .jQWCP-wWidget.jQWCP-block");c.each(function(){var b=a(this).data("jQWCP.instance");b.refreshWidget(),b.redrawSliders()})},b.Handler.overlay_click=function(c){if(null!=b.ColorPicker.widget){var d=a(b.ColorPicker.widget),e=d.data("jQWCP.instance");if(null!=e){var f=a(e.input);e.lastValue!=e.input.value&&f.trigger("change"),e.hide()}}},a(document).ready(function(){a("[data-wheelcolorpicker]").wheelColorPicker({htmlOptions:!0})}),function(){void 0!=a.browser&&a.browser.mozilla&&(a.fn.wheelColorPicker.defaults.quality=.2),a(document).ready(function(){a("body").append('<div id="jQWCP-PageOrigin" style="position: absolute; top: 0; left: 0; height: 0; width: 0;"></div>');var c=document.getElementById("jQWCP-PageOrigin").getBoundingClientRect();b.ORIGIN=c,a(window).on("scroll.jQWCP_RelativePageOriginBugFix",function(){var a=document.getElementById("jQWCP-PageOrigin").getBoundingClientRect();b.ORIGIN=a,0==a.left&&0==a.top||(b.BUG_RELATIVE_PAGE_ORIGIN=!0)})})}()}(jQuery);
