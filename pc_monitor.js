// ================================
// PC Monitoring
// ================================

let pcs = [
    {
        id: 1,
        name: "PC01",
        status: "Busy",
        user: "lam123",
        time: "01:25:10"
    },
    {
        id: 2,
        name: "PC02",
        status: "Available",
        user: "-",
        time: "-"
    },
    {
        id: 3,
        name: "PC03",
        status: "Offline",
        user: "-",
        time: "-"
    },
    {
        id: 4,
        name: "PC04",
        status: "Busy",
        user: "nam456",
        time: "00:45:38"
    },
    {
        id: 5,
        name: "PC05",
        status: "Maintenance",
        user: "-",
        time: "-"
    },
    {
        id: 6,
        name: "PC06",
        status: "Available",
        user: "-",
        time: "-"
    },
    {
        id: 7,
        name: "PC07",
        status: "Busy",
        user: "hoa789",
        time: "02:10:12"
    },
    {
        id: 8,
        name: "PC08",
        status: "Available",
        user: "-",
        time: "-"
    }
];

// ================================
// Load Table
// ================================

function loadPCs() {

    const table = document.getElementById("pcTable");

    table.innerHTML = "";

    let available = 0;
    let busy = 0;
    let offline = 0;

    pcs.forEach(pc => {

        if (pc.status === "Available") available++;
        if (pc.status === "Busy") busy++;
        if (pc.status === "Offline") offline++;

        table.innerHTML += `

        <tr>

            <td>${pc.id}</td>

            <td>${pc.name}</td>

            <td class="${pc.status.toLowerCase()}">

                ${pc.status}

            </td>

            <td>${pc.user}</td>

            <td>${pc.time}</td>

        </tr>

        `;

    });

    document.getElementById("totalPC").textContent = pcs.length;
    document.getElementById("availablePC").textContent = available;
    document.getElementById("busyPC").textContent = busy;
    document.getElementById("offlinePC").textContent = offline;

    // Lưu danh sách PC vào localStorage để trang Reports đọc dữ liệu thật
    localStorage.setItem("pcs", JSON.stringify(pcs));
}

// ================================
// Search
// ================================

function searchPC() {

    const keyword = document
        .getElementById("searchInput")
        .value
        .toLowerCase();

    const table = document.getElementById("pcTable");

    table.innerHTML = "";

    pcs.filter(pc =>
        pc.name.toLowerCase().includes(keyword)
    )

    .forEach(pc => {

        table.innerHTML += `

        <tr>

            <td>${pc.id}</td>

            <td>${pc.name}</td>

            <td class="${pc.status.toLowerCase()}">

                ${pc.status}

            </td>

            <td>${pc.user}</td>

            <td>${pc.time}</td>

        </tr>

        `;

    });

}

// ================================
// Auto Refresh
// ================================

setInterval(() => {

    loadPCs();

}, 5000);

// ================================

window.onload = function () {

    loadPCs();

}
function logout(){

    if(confirm("Đăng xuất?")){

        localStorage.removeItem("admin");

        window.location.href="login.html";

    }

}