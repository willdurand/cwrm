/* This file has been automatically generated, do not edit it */

#ifndef CWRM_GENERATED_H
#define CWRM_GENERATED_H

#define AP_NAME "Camera WiFi Remote Module"

const String indexHTML = R"(<!doctype html>
<title>Camera WiFi Remote Module</title>
<style>#focus-btn,#shutter-btn{background-color:#6a5acd;border:0;border-radius:5px;width:100%;max-width:250px;padding:10px;color:#fff;font-size:1rem}#focus-btn{background-color:#009688}#every-input{text-align:center;width:50px}button:active{background-image:none;outline:0;-webkit-box-shadow:inset 0 3px 5px rgba(0,0,0,.125);box-shadow:inset 0 3px 5px rgba(0,0,0,.125)}button:disabled{opacity:.65;cursor:not-allowed}</style>
<body style="text-align:center">
    <h1>Camera WiFi Remote Module</h1>
    <p><button id="shutter-btn">take picture</button></p>
    <p>
        Every <input id="every-input" type="number" value="5"> seconds
        <button id="every-btn">start</button>
    </p>
    <p style="padding-top:1rem"><button id="focus-btn">focus</button></p>
    <p><small>v1.1.0</small></p>
    <script>!function(t,e){function n(t){return t&&e.XDomainRequest&&!/MSIE 1/.test(navigator.userAgent)?new XDomainRequest:e.XMLHttpRequest?new XMLHttpRequest:void 0}function o(t,e,n){t[e]=t[e]||n}var r=["responseType","withCredentials","timeout","onprogress"];t.ajax=function(t,a){function s(t,e){return function(){c||(a(void 0===f.status?t:f.status,0===f.status?"Error":f.response||f.responseText||e,f),c=!0)}}var u=t.headers||{},i=t.body,d=t.method||(i?"POST":"GET"),c=!1,f=n(t.cors);f.open(d,t.url,!0);var l=f.onload=s(200);f.onreadystatechange=function(){4===f.readyState&&l()},f.onerror=s(null,"Error"),f.ontimeout=s(null,"Timeout"),f.onabort=s(null,"Abort"),i&&(o(u,"X-Requested-With","XMLHttpRequest"),e.FormData&&i instanceof e.FormData||o(u,"Content-Type","application/x-www-form-urlencoded"));for(var p,m=0,v=r.length;v>m;m++)p=r[m],void 0!==t[p]&&(f[p]=t[p]);for(var p in u)f.setRequestHeader(p,u[p]);return f.send(i),f},e.nanoajax=t}({},function(){return this}())</script>
    <script>var interval=!1,$shutterBtn=document.querySelector("#shutter-btn"),$focusBtn=document.querySelector("#focus-btn"),$everyInput=document.querySelector("#every-input"),$everyBtn=document.querySelector("#every-btn"),trigger=function(t,e){t.setAttribute("disabled","disabled"),nanoajax.ajax({url:e,method:"POST"},function(e,r){t.removeAttribute("disabled")})},startInterval=function(){var t=parseInt($everyInput.value,10);NaN===t||t<1||(trigger($shutterBtn,"/trigger/shutter"),interval=setInterval(function(){trigger($shutterBtn,"/trigger/shutter")},1e3*t),$everyBtn.innerHTML="stop")},stopInterval=function(){interval&&(clearInterval(interval),interval=!1,$everyBtn.innerHTML="start")};$shutterBtn.addEventListener("click",function(){trigger($shutterBtn,"/trigger/shutter")},!1),$focusBtn.addEventListener("click",function(){trigger($focusBtn,"/trigger/focus")},!1),$everyBtn.addEventListener("click",function(){if(interval)return void stopInterval();startInterval()},!1)</script>)";

#endif
