const ADMIN_USERNAME="admin";

const ADMIN_PASSWORD="123456";

function login(){

const username=document
.getElementById("username")
.value
.trim();

const password=document
.getElementById("password")
.value
.trim();

const message=document
.getElementById("message");

if(username===""||password===""){

message.textContent="Please enter username and password.";

return;

}

if(username===ADMIN_USERNAME&&password===ADMIN_PASSWORD){

localStorage.setItem("admin",username);

window.location.href="admin_dashboard.html";

}

else{

message.textContent="Invalid username or password.";

}

}

document.addEventListener("keydown",function(e){

if(e.key==="Enter"){

login();

}

});