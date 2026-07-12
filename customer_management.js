// ===============================
// Customer Management
// ===============================

let customers = JSON.parse(localStorage.getItem("customers"));

if (!customers) {

    customers = [

        {
            id: 1,
            username: "lam123",
            fullname: "Vũ Bình Lâm",
            balance: 150000,
            status: "Online"
        },

        {
            id: 2,
            username: "nam456",
            fullname: "Nguyễn Văn Nam",
            balance: 80000,
            status: "Offline"
        }

    ];

    localStorage.setItem(
        "customers",
        JSON.stringify(customers)
    );

}
function saveCustomers(){

    localStorage.setItem(
        "customers",
        JSON.stringify(customers)
    );

}

// ===============================
// Transaction Log (dùng cho trang Reports)
// ===============================

function logTransaction(username, amount){

    // Chỉ ghi log khi có tiền nạp thêm (amount > 0)
    if(amount <= 0) return;

    const transactions =
    JSON.parse(localStorage.getItem("transactions")) || [];

    transactions.push({
        username: username,
        amount: amount,
        date: new Date().toISOString()
    });

    localStorage.setItem(
        "transactions",
        JSON.stringify(transactions)
    );

}
// ===============================
// Load Customer
// ===============================

function loadCustomers() {

    const table = document.getElementById("customerTable");

    table.innerHTML = "";

    customers.forEach(customer => {

        table.innerHTML += `

        <tr>

            <td>${customer.id}</td>

            <td>${customer.username}</td>

            <td>${customer.fullname}</td>

            <td>${customer.balance.toLocaleString("vi-VN")} VNĐ</td>

            <td class="${customer.status==="Online"?"online":"offline"}">

                ${customer.status}

            </td>

            <td>

                <button class="editBtn"
                        onclick="editCustomer(${customer.id})">

                    Edit

                </button>

                <button class="deleteBtn"
                        onclick="deleteCustomer(${customer.id})">

                    Delete

                </button>

            </td>

        </tr>

        `;

    });

}

// ===============================
// Search
// ===============================

function searchCustomer(){

    const keyword =
    document.getElementById("searchInput")
    .value
    .toLowerCase();

    const table =
    document.getElementById("customerTable");

    table.innerHTML="";

    customers
    .filter(c=>

        c.username.toLowerCase().includes(keyword)

        ||

        c.fullname.toLowerCase().includes(keyword)

    )

    .forEach(customer=>{

        table.innerHTML+=`

        <tr>

        <td>${customer.id}</td>

        <td>${customer.username}</td>

        <td>${customer.fullname}</td>

        <td>${customer.balance.toLocaleString("vi-VN")} VNĐ</td>

        <td class="${customer.status==="Online"?"online":"offline"}">

        ${customer.status}

        </td>

        <td>

        <button class="editBtn"

        onclick="editCustomer(${customer.id})">

        Edit

        </button>

        <button class="deleteBtn"

        onclick="deleteCustomer(${customer.id})">

        Delete

        </button>

        </td>

        </tr>

        `;

    });

}

// ===============================
// Delete
// ===============================

function deleteCustomer(id){

    if(confirm("Delete customer?")){

        customers =
        customers.filter(c=>c.id!==id);

        saveCustomers();

        loadCustomers();

    }

}

// ===============================
// Edit
// ===============================

function editCustomer(id){

    const customer =
    customers.find(c=>c.id===id);

    const money =
    prompt("New Balance", customer.balance);

    if(money!==null){

        const newBalance = Number(money);
        const added = newBalance - customer.balance;

        customer.balance = newBalance;

        // Ghi log giao dịch nếu là nạp thêm tiền
        logTransaction(customer.username, added);

        saveCustomers();

        loadCustomers();

    }

}

// ===============================
// Add
// ===============================

function addCustomer(){

    const username = prompt("Username");

    if(!username) return;

    const fullname = prompt("Full Name");

    if(!fullname) return;

    const balance = Number(prompt("Balance"));

    customers.push({

        id: Date.now(),

        username,

        fullname,

        balance,

        status:"Offline"

    });

    // Ghi log giao dịch nạp tiền ban đầu
    logTransaction(username, balance);

    saveCustomers();

    loadCustomers();

}
// ===============================

window.onload=function(){

    loadCustomers();

}
function logout(){

    if(confirm("Đăng xuất?")){

        localStorage.removeItem("admin");

        window.location.href="login.html";

    }

}