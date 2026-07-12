// Lấy dữ liệu khách hàng
const customers = JSON.parse(localStorage.getItem("customers")) || [];

// Hiển thị số lượng khách
document.getElementById("customerCount").textContent = customers.length;

// Tính tổng số dư của tất cả khách hàng
let total = 0;

customers.forEach(c => {
    total += c.balance;
});

// Hiển thị tổng số dư
document.getElementById("revenue").textContent =
    total.toLocaleString("vi-VN") + " VNĐ";

// Dữ liệu mẫu cho PC
document.getElementById("onlinePC").textContent = 22;
document.getElementById("offlinePC").textContent = 8;