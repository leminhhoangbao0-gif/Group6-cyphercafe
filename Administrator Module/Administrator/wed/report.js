// ===============================
// Report Data (đọc thật từ localStorage)
// ===============================

// Danh sách khách hàng
const customers = JSON.parse(localStorage.getItem("customers")) || [];

// Lịch sử giao dịch (được ghi lại từ customer_management.js mỗi khi nạp tiền)
const transactions = JSON.parse(localStorage.getItem("transactions")) || [];

// Danh sách PC (được ghi lại từ pc_monitor.js)
const pcs = JSON.parse(localStorage.getItem("pcs")) || [];

// ===============================
// Helper: kiểm tra ngày
// ===============================

function isToday(dateStr){
    const d = new Date(dateStr);
    const now = new Date();
    return d.getFullYear() === now.getFullYear()
        && d.getMonth() === now.getMonth()
        && d.getDate() === now.getDate();
}

function isThisMonth(dateStr){
    const d = new Date(dateStr);
    const now = new Date();
    return d.getFullYear() === now.getFullYear()
        && d.getMonth() === now.getMonth();
}

// Chuyển chuỗi thời gian "hh:mm:ss" sang số giờ (số thập phân)
function timeStringToHours(timeStr){
    if(!timeStr || timeStr === "-") return 0;
    const parts = timeStr.split(":").map(Number);
    const hours = parts[0] || 0;
    const minutes = parts[1] || 0;
    const seconds = parts[2] || 0;
    return hours + minutes / 60 + seconds / 3600;
}

// ===============================
// Doanh thu & Sessions (từ transactions thật)
// ===============================

const report = {

    todayRevenue: transactions
        .filter(t => isToday(t.date))
        .reduce((sum, t) => sum + t.amount, 0),

    monthRevenue: transactions
        .filter(t => isThisMonth(t.date))
        .reduce((sum, t) => sum + t.amount, 0),

    totalSessions: transactions.length

};

// ===============================
// Top Customers (tổng tiền đã nạp, từ transactions thật)
// ===============================

let topCustomers = [];

if(transactions.length > 0){

    // Gộp tổng số tiền đã nạp theo từng username
    const spentMap = {};

    transactions.forEach(t => {
        spentMap[t.username] = (spentMap[t.username] || 0) + t.amount;
    });

    topCustomers = Object.keys(spentMap)
        .map(username => ({ username, spent: spentMap[username] }))
        .sort((a, b) => b.spent - a.spent)
        .slice(0, 5);

}else{

    // Chưa có giao dịch nào -> tạm xếp theo số dư hiện tại
    topCustomers = customers
        .map(c => ({ username: c.username, spent: c.balance }))
        .sort((a, b) => b.spent - a.spent)
        .slice(0, 5);

}

// ===============================
// Top PCs (theo thời gian sử dụng hiện tại, từ pcs thật)
// ===============================

const topPCs = pcs
    .map(pc => ({ pc: pc.name, hours: timeStringToHours(pc.time) }))
    .filter(p => p.hours > 0)
    .sort((a, b) => b.hours - a.hours)
    .slice(0, 5);

// ===============================
// Dashboard Cards
// ===============================

document.getElementById("todayRevenue").textContent =
report.todayRevenue.toLocaleString("vi-VN") + " VNĐ";

document.getElementById("monthRevenue").textContent =
report.monthRevenue.toLocaleString("vi-VN") + " VNĐ";

document.getElementById("sessions").textContent =
report.totalSessions;

document.getElementById("customers").textContent =
customers.length;

// ===============================
// Top Customer Table
// ===============================

const customerTable =
document.getElementById("topCustomer");

if(topCustomers.length === 0){

    customerTable.innerHTML = `<tr><td colspan="2">Chưa có dữ liệu</td></tr>`;

}else{

    topCustomers.forEach(customer => {

        customerTable.innerHTML += `
        <tr>
            <td>${customer.username}</td>
            <td>${customer.spent.toLocaleString("vi-VN")} VNĐ</td>
        </tr>
        `;

    });

}

// ===============================
// Top PC Table
// ===============================

const pcTable =
document.getElementById("topPC");

if(topPCs.length === 0){

    pcTable.innerHTML = `<tr><td colspan="2">Chưa có dữ liệu</td></tr>`;

}else{

    topPCs.forEach(pc => {

        pcTable.innerHTML += `
        <tr>
            <td>${pc.pc}</td>
            <td>${pc.hours.toFixed(1)} h</td>
        </tr>
        `;

    });

}

// ===============================
// Revenue Chart (7 ngày gần nhất, tính từ transactions thật)
// ===============================

const last7Days = [];
const last7Labels = [];

for(let i = 6; i >= 0; i--){

    const d = new Date();
    d.setDate(d.getDate() - i);

    const dayTotal = transactions
        .filter(t => {
            const td = new Date(t.date);
            return td.getFullYear() === d.getFullYear()
                && td.getMonth() === d.getMonth()
                && td.getDate() === d.getDate();
        })
        .reduce((sum, t) => sum + t.amount, 0);

    last7Days.push(dayTotal);
    last7Labels.push(d.toLocaleDateString("vi-VN", { weekday: "short" }));

}

const ctx =
document.getElementById("revenueChart");

new Chart(ctx, {

    type: "bar",

    data: {

        labels: last7Labels,

        datasets: [

            {
                label: "Revenue",
                data: last7Days,
                backgroundColor: "#2563eb",
                borderRadius: 8
            }

        ]

    },

    options:{

        responsive:true,

        plugins:{

            legend:{
                display:false
            }

        },

        scales:{

            y:{
                beginAtZero:true
            }

        }

    }

});

function logout(){

    if(confirm("Đăng xuất?")){

        localStorage.removeItem("admin");

        window.location.href="login.html";

    }

}
