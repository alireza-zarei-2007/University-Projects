# 🚚 UT-Truck Management System

A centralized freight, logistics, and shipping management system written in C++ (Advanced Programming). The application optimizes parcel shipping, dynamically allocates trucks based on payload and order priority, tracks shipment life cycles, and provides comprehensive financial reports.

---

## 📌 Description

**UT-Truck** manages a centralized transportation network structured as a **Star Topology** around Tehran. Incoming and outgoing orders are queued in central/local warehouses, dynamically prioritized using age-weight scoring formulas, loaded into optimal trucks, and tracked through three core states: `Warehouse`, `In Transit`, and `Delivered`.

---

## 🏗 System Architecture

The transport network operates strictly around Tehran as the central hub node:
* **Central Hub:** Tehran (Distance = 0).
* **Peripheral Nodes:** All other cities connect directly **only** to Tehran.
* **No Direct Routes:** Direct travel between non-Tehran peripheral cities is not permitted.
* **Fleet Routing:** All trucks originate in Tehran and stay at their destination city upon parcel delivery until further commands are issued.
* [City A]
      \
       \
[City B] --- ( Tehran Central Hub ) --- [City C]
/
/
[City D]
