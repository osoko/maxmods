| **Version** | **Date** | **Comments** |
|:------------|:---------|:-------------|
| 1.10 | 7 Mar 2008 | Update to SQLite 3.5.6. |
|  |  | Fixed lack of error reporting during query execution. |
|  |  | Transaction queries are finalized more quickly. |
|  |  | Statement should generally be reset before acquiring error message. |
| 1.09 | - | Update to SQLite 3.5.2. Now using the Amalgamated version. |
|  |  | Implementation of Date, DateTime and Time types. |
| 1.08 | 28 Sep 2007 | Fixed null column types not being handled. |
| 1.07 | - | Fixed problem with lastInsertedId() not returning.. the last inserted id. |
| 1.06 | - | Update to SQLite 3.4.2. |
| 1.05 | - | Fixed database Close to cleanup non-finalized queries. |
| 1.04 | - | Improved error message details. |
| 1.03 | - | Fixed NextRow returning True on empty queries. |
| 1.02 | - | Fixed issue with mis-count of bound parameters. |
| 1.01 | - | Added hasPrepareSupport() and hasTransactionSupport() methods. |
| 1.00 | - | Initial Release. Includes SQLite 3.3.13 source. |