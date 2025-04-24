// Peta Rumania dalam bentuk object
// Setiap root node memegang cabang(tetangga)-nya masing-masing
const graph = {
  Arad: ["Zerind", "Timisoara", "Sibiu"],
  Zerind: ["Arad", "Oradea"],
  Oradea: ["Zerind", "Sibiu"],
  Sibiu: ["Arad", "Oradea", "Fagaras", "Rimnicu"],
  Timisoara: ["Arad", "Lugoj"],
  Lugoj: ["Timisoara", "Mehadia"],
  Mehadia: ["Lugoj", "Dobreta"],
  Dobreta: ["Mehadia", "Craiova"],
  Craiova: ["Dobreta", "Rimnicu", "Pitesti"],
  Rimnicu: ["Sibiu", "Craiova", "Pitesti"],
  Fagaras: ["Sibiu", "Bucharest"],
  Pitesti: ["Rimnicu", "Craiova", "Bucharest"],
  Bucharest: ["Fagaras", "Pitesti", "Giurgiu", "Urziceni"],
  Giurgiu: ["Bucharest"],
  Urziceni: ["Bucharest", "Vaslui", "Hirsova"],
  Hirsova: ["Urziceni", "Eforie"],
  Eforie: ["Hirsova"],
  Vaslui: ["Urziceni", "Lasi"],
  Lasi: ["Vaslui", "Neamt"],
  Neamt: ["Lasi"],
};

/**
 * Implementasi BFS yang menelusuri per-level untuk mencari jalur terpendek.
 *
 * @param   {string} start  Node awal.
 * @param   {string} goal  Node akhir(tujuan).
 * @returns {Array|null}  Array berisi jalur terpendek jika ditemukan, jika tidak maka `null`.
 */
function bfs(start, goal) {
  // Pastikan start dan goal ada dalam graph
  if (!(start in graph) || !(goal in graph)) {
    console.log("Node tidak ditemukan dalam graph.");
    return null;
  }
  // Inisiasi variabel antrian dalam pencarian jalur
  let queue = [[start]]; // Antrian array dimulai dari object milik params start

  // Inisiasi variabel visited yang menyimpan node yang sudah pernah dikunjugi
  let visited = new Set(); // Membuat set untuk menyimpan kumpulan node dalam array

  // Looping antrian ketika isinya lebih dari 0
  while (queue.length > 0) {
    // Mengambil jalur pertama dari antrian
    let path = queue.shift();

    // Mengambil node terakhir dari jalur antrian(saat ini)
    let node = path[path.length - 1];

    // Jika node terakhir yang ditelusuri == goal, maka keluar dari loop dan return jalur yang sudah ditelusuri
    if (node === goal) {
      return path;
    }

    // Menelusuri semua neighbour (tetangga) dari node saat ini
    for (let neighbour of graph[node]) {
      // Memastikan bahwa node tetangga tersebut belum dikunjungi
      if (!visited.has(neighbour)) {
        // Menambahkan node tetangga saat ini kedalam array visited
        visited.add(neighbour);

        // Menginisiasi path baru dari gabungan array path dengan neighbour
        let newPath = [...path, neighbour];

        // Memasukkan variabel newPath kedalam antrian penelusuran
        queue.push(newPath);
      }
    }
  }
  // Jika tidak ada kondisi yang memenuhi return null
  return null;
}

const start = "Arad";
const goal = "Neamt";
console.log("BFS Path:", bfs(start, goal));
