<div align="center">

  <h1>🚚 UT-Truck Logistics Engine</h1>
  <p><b>Advanced Programming Project | C++ Centralized Transport Management System</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C%2B%2B11-blue.svg" alt="C++11">
    <img src="https://img.shields.io/badge/Architecture-Star--Topology-orange.svg" alt="Star Topology">
    <img src="https://img.shields.io/badge/Build-g%2B%2B-green.svg" alt="g++ Build">
  </p>

</div>

---

<h2>📌 Description</h2>
<p>
<b>UT-Truck</b> is a high-performance C++ freight management application built around a <b>Star Topology network</b> centered in <b>Tehran</b>. 
The system manages incoming/outgoing orders, queues them in warehouses, sorts them using a dynamic prioritization algorithm (based on weight and order age), packs optimal trucks, tracks shipment lifecycles, and provides financial reports.
</p>

---

<h2>🏗️ System Network Architecture</h2>

<div align="center">
  <pre>
                  [City A]
                     \
                      \
   [City B] ------- ( Tehran Central Hub ) ------- [City C]
                      /
                     /
                  [City D]
  </pre>
</div>

<ul>
  <li><b>Central Hub:</b> Tehran is the origin or destination for all routes (Distance = 0).</li>
  <li><b>Star Topology:</b> No direct paths exist between peripheral cities.</li>
  <li><b>Fleet Relocation:</b> Trucks start in Tehran and remain at their destination city upon delivery until further operations.</li>
</ul>

---

<h2>📁 Input File Specifications</h2>

<p>The program takes two <code>CSV</code> data files as command-line arguments upon startup:</p>

<table>
  <thead>
    <tr>
      <th>File Type</th>
      <th>CLI Argument Position</th>
      <th>Format Example</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><b>Trucks Data</b></td>
      <td><code>argv[1]</code></td>
      <td>
        <pre>truck_id,capacity
1,100
2,150</pre>
      </td>
    </tr>
    <tr>
      <td><b>Cities Data</b></td>
      <td><code>argv[2]</code></td>
      <td>
        <pre>city_name,distance
Arak,500
Isfahan,700</pre>
      </td>
    </tr>
  </tbody>
</table>

---

<h2>🕹️ Available Commands & Formats</h2>

<h3>1. Register Order (<code>add_order</code>)</h3>
<p>Adds a new shipment to the system with an auto-incrementing ID starting from <code>1</code>.</p>

<b>Input Format:</b>
<pre>add_order &lt;origin_city&gt; &lt;destination_city&gt; &lt;weight&gt;</pre>

<b>Sample Code Input:</b>
<pre>add_order Tehran Arak 50</pre>

<b>Sample Code Output:</b>
<pre>Order 1 added</pre>

<hr>

<h3>2. Track Status (<code>track</code>)</h3>
<p>Queries the exact current location and status of a parcel.</p>

<b>Input Format:</b>
<pre>track &lt;order_id&gt;</pre>

<b>Possible Outputs:</b>
<pre>Order 1 is currently in warehouse in Tehran
Order 1 is in transit to Arak
Order 1 is delivered to Arak
Order not found</pre>

<hr>

<h3>3. Load Cargo (<code>load</code>)</h3>
<p>Packs waiting warehouse orders into the specified truck based on priority scores without exceeding capacity.</p>

<b>Input Format:</b>
<pre>load &lt;truck_id&gt; &lt;destination_city&gt;</pre>

<b>Sample Code Input:</b>
<pre>load 1 Arak</pre>

<b>Sample Code Output:</b>
<pre>Truck 1 loaded with orders: 1 3 5</pre>

<hr>

<h3>4. Deliver Cargo (<code>deliver</code>)</h3>
<p>Marks all cargo inside the specified truck as delivered to the target city.</p>

<b>Input Format:</b>
<pre>deliver &lt;truck_id&gt;</pre>

<b>Sample Code Input:</b>
<pre>deliver 1</pre>

<b>Sample Code Output:</b>
<pre>Truck 1 delivered orders: 1 3 5</pre>

<hr>

<h3>5. Route Recommendation Engine (<code>recommend</code>)</h3>
<p>Suggests the optimal target city and the best-fitting available truck in Tehran with minimal leftover space.</p>

<b>Input Format:</b>
<pre>recommend</pre>

<b>Sample Code Output:</b>
<pre>Recommended city: Arak
Recommended truck: 4</pre>

<hr>

<h3>6. Financial Summary (<code>financial_report</code>)</h3>
<p>Calculates total earned revenue based on delivered parcels only.</p>

<b>Input Format:</b>
<pre>financial_report</pre>

<b>Sample Code Output:</b>
<pre>Total income: 50000
Delivered orders:
1 25000
3 15000
5 10000</pre>

---

<h2>🧮 Logic & Mathematical Models</h2>

<details>
  <summary><b>Click to expand Priority Score Formula</b></summary>
  <br>
  <p>To prioritize older and heavier orders:</p>
  <code>Score = Weight + (LargestOrderID - OrderID) * 5</code>
  <p><i>Note: If scores tie, the order with the smaller Order ID takes precedence.</i></p>
</details>

<details>
  <summary><b>Click to expand City Recommendation Formula</b></summary>
  <br>
  <code>CityScore = (SumOutgoingScores + SumIncomingScores) / Distance(City)</code>
  <p><i>Note: If scores tie, the city with alphabetical priority is chosen.</i></p>
</details>

<details>
  <summary><b>Click to expand Shipping Cost Calculation</b></summary>
  <br>
  <code>Cost = Distance * Weight</code>
</details>

---

<h2>⚙️ System Validation Rules</h2>

<table>
  <tr>
    <td><b>Origin / Destination</b></td>
    <td>Exactly one of origin or destination must be <b>Tehran</b>.</td>
  </tr>
  <tr>
    <td><b>Unique Identifiers</b></td>
    <td>Truck IDs in CSV and system-generated Order IDs are strictly unique.</td>
  </tr>
  <tr>
    <td><b>Output Sorting</b></td>
    <td>Order lists printed in <code>load</code>, <code>deliver</code>, and <code>financial_report</code> outputs are sorted in <b>ascending order</b>.</td>
  </tr>
</table>

---

<h2>🛠️ Build & Run Instructions</h2>

<p>1. Compile the project source code:</p>
<pre>g++ -std=c++11 -O2 main.cpp -o UTTruck</pre>

<p>2. Launch executable with CSV path arguments:</p>
<pre>./UTTruck ./trucks.csv ./cities.csv</pre>

---
