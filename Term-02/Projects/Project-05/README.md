<div align="center">

  <h1>🚚 UT-Truck Management System</h1>
  <p><b>Advanced Programming (AP) Project | C++ Centralized Transport & Logistics Engine</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C%2B%2B11-blue.svg" alt="C++11">
    <img src="https://img.shields.io/badge/Architecture-Star--Topology-orange.svg" alt="Star Topology">
    <img src="https://img.shields.io/badge/Build-g%2B%2B-green.svg" alt="g++ Build">
  </p>

</div>

---

<h2>📌 Overview & Introduction</h2>
<p>
<b>UT-Truck</b> is a centralized freight and parcel logistics management system designed in C++ using Object-Oriented Programming (OOP) principles. The system handles parcel registration, dynamic order prioritization, real-time shipment lifecycle tracking, optimized truck loading, route/truck recommendations, and financial report generation.
</p>

---

<h2>🏗️ System Network Architecture</h2>

<div align="center">
  <pre>
                  [Peripheral City A]
                          \
                           \
   [Peripheral City B] --- ( Tehran Central Hub ) --- [Peripheral City C]
                           /
                          /
                  [Peripheral City D]
  </pre>
</div>

<ul>
  <li><b>Central Hub:</b> Tehran acts as the central hub (Distance = 0). All freight originates from or is destined for Tehran.</li>
  <li><b>Star Topology:</b> No direct paths exist between peripheral cities.</li>
  <li><b>Fleet Relocation:</b> All trucks initially start in Tehran. Upon delivering cargo to a destination city, the truck remains in that city until loaded again.</li>
</ul>

---

<h2>🚀 Program Execution & Input Formats</h2>

<p>The system is executed via Command Line Interface (CLI) by supplying paths to two input CSV configuration files:</p>

<pre>./UTTruck &lt;/path/to/trucks.csv&gt; &lt;/path/to/cities.csv&gt;</pre>

<h3>1. Trucks Data File (<code>trucks.csv</code>)</h3>
<p>Contains unique truck identifiers and their maximum natural payload weight capacities (no spaces).</p>
<pre>truck_id, capacity
1,100
2,150
3,200
4,50</pre>

<h3>2. Cities Data File (<code>cities.csv</code>)</h3>
<p>Contains city names (no spaces) and their natural distance to Tehran in kilometers.</p>
<pre>city_name, distance
Arak, 500
Isfahan, 700</pre>

---

<h2>🕹️ Commands & CLI Interactions</h2>

<h3>1. Add New Order (<code>add_order</code>)</h3>
<p>Registers a parcel into the warehouse. Assigns a unique auto-incrementing <code>order_id</code> starting from <code>1</code>.</p>

<b>Input Format:</b>
<pre>add_order &lt;origin_city&gt; &lt;destination_city&gt; &lt;weight&gt;</pre>

<b>Sample Code Input:</b>
<pre>add_order Tehran Arak 50</pre>

<b>Sample Code Output:</b>
<pre>Order 1 added</pre>

<hr>

<h3>2. Track Order Status (<code>track</code>)</h3>
<p>Displays the current lifecycle state of an order (<code>Warehouse</code>, <code>In Transit</code>, or <code>Delivered</code>).</p>

<b>Input Format:</b>
<pre>track &lt;order_id&gt;</pre>

<b>Sample Code Input:</b>
<pre>track 1</pre>

<b>Sample Code Output Options:</b>
<pre>Order 1 is currently in warehouse in Tehran
Order 1 is in transit to Arak
Order 1 is delivered to Arak
Order not found</pre>

<hr>

<h3>3. Load Truck (<code>load</code>)</h3>
<p>Filters matching warehouse orders, sorts them by priority score, and packs them into the specified truck without exceeding payload limits. The truck immediately dispatches upon loading.</p>

<b>Input Format:</b>
<pre>load &lt;truck_id&gt; &lt;destination_city&gt;</pre>

<b>Sample Code Input:</b>
<pre>load 1 Arak</pre>

<b>Sample Code Output Options:</b>
<pre>Truck 1 loaded with orders: 1 3 5
No order could be loaded</pre>

<hr>

<h3>4. Deliver Orders (<code>deliver</code>)</h3>
<p>Updates all orders carried by the specified truck from <code>In Transit</code> to <code>Delivered</code>.</p>

<b>Input Format:</b>
<pre>deliver &lt;truck_id&gt;</pre>

<b>Sample Code Input:</b>
<pre>deliver 1</pre>

<b>Sample Code Output Options:</b>
<pre>Truck 1 delivered orders: 1 3 5
No orders to deliver in truck 1</pre>

<hr>

<h3>5. Recommend City & Truck (<code>recommend</code>)</h3>
<p>Calculates the optimal target city based on active parcel scores over distance, then suggests an available truck in Tehran with minimal leftover capacity.</p>

<b>Input Format:</b>
<pre>recommend</pre>

<b>Sample Code Output:</b>
<pre>Recommended city: Arak
Recommended truck: 4</pre>

<hr>

<h3>6. Financial Summary (<code>financial_report</code>)</h3>
<p>Computes total earnings generated solely from parcels with a status of <code>Delivered</code>.</p>

<b>Input Format:</b>
<pre>financial_report</pre>

<b>Sample Code Output:</b>
<pre>Total income: 50000
Delivered orders:
1 25000
3 15000
5 10000</pre>

---

<h2>🧮 Mathematical Formulas & Algorithm Logic</h2>

<details>
  <summary><b>1. Order Priority Score Calculation</b></summary>
  <br>
  <p>To prioritize older and heavier parcels during loading and route calculations:</p>
  <code>Score = Weight + (LargestOrderID - OrderID) * 5</code>
  <p><i>Note: If two orders have equal scores, the order registered earlier (smaller <code>OrderID</code>) takes priority.</i></p>
</details>

<details>
  <summary><b>2. City Recommendation Score Formula</b></summary>
  <br>
  <code>CityScore = (SumOutgoingScores + SumIncomingScores) / Distance(City)</code>
  <ul>
    <li><b>SumOutgoingScores:</b> Sum of scores for active parcels traveling from target city to Tehran.</li>
    <li><b>SumIncomingScores:</b> Sum of scores for active parcels traveling from Tehran to target city.</li>
    <li><i>Tie-breaker: If multiple cities share the top score, the alphabetically smaller city name is selected.</i></li>
  </ul>
</details>

<details>
  <summary><b>3. Truck Allocation Logic</b></summary>
  <br>
  <p>From available trucks currently stationed in Tehran with sufficient capacity, selects the truck that will have the <b>minimal leftover empty capacity</b> after loading the target city's cargo. If equal, chooses the one with the smallest <code>truck_id</code>.</p>
</details>

<details>
  <summary><b>4. Shipping Cost Calculation</b></summary>
  <br>
  <code>Cost = Distance * Weight</code>
</details>

---

<h2>⚙️ System Constraints & Validation Rules</h2>

<table>
  <tr>
    <th>Category</th>
    <th>Constraint / Requirement</th>
  </tr>
  <tr>
    <td><b>Hub Rule</b></td>
    <td>Either the origin city or the destination city of any order <b>must</b> be Tehran.</td>
  </tr>
  <tr>
    <td><b>IDs & Uniqueness</b></td>
    <td>Truck IDs and Order IDs are strictly unique. Order IDs automatically start at <code>1</code>.</td>
  </tr>
  <tr>
    <td><b>Output Ordering</b></td>
    <td>Order IDs printed in <code>load</code>, <code>deliver</code>, and <code>financial_report</code> commands must always be sorted in <b>ascending order</b>.</td>
  </tr>
  <tr>
    <td><b>Strict Formatting</b></td>
    <td>Outputs are auto-graded and must strictly match single spaces, line breaks, and exact casing.</td>
  </tr>
</table>

---

<h2>💻 Code Quality & Implementation Guidelines</h2>

<ul>
  <li><b>No Magic Values:</b> All constants are explicitly named and defined.</li>
  <li><b>Modern C++ STL Containers:</b> Uses standard library containers (e.g., <code>std::vector</code>, <code>std::map</code>) and iterators instead of C-style arrays.</li>
  <li><b>Modular OOP Design:</b> Clean single-responsibility functions and avoidance of global variables.</li>
</ul>

---

<h2>🛠️ Compilation & Setup</h2>

<p>1. Compile the C++ source file using standard <code>g++</code> compiler flags:</p>
<pre>g++ -std=c++11 -O2 main.cpp -o UTTruck</pre>

<p>2. Execute with sample test arguments:</p>
<pre>./UTTruck ./trucks.csv ./cities.csv</pre>

---
