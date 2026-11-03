/*
 * Nombre: [Jose Vera]
 * Fecha: 11/4/2026
 * Práctica de vistas filtradas utilizando un arreglo de punteros 
 * para gestionar órdenes de prueba (OrderPreview) sin alterar la colección original.
 */

#include <iostream>
#include <string>

using namespace std;

// Struct Definition for OrderPreview
struct OrderPreview
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

// Prototypes for functions to display orders and views
void displayOrders(const OrderPreview orders[], int count, const string& title);
void displayView(OrderPreview *view[], int count, const string& title);

int main()
{
    const int CAPACITY = 4;

    // E1 & E3: Cuatro registros dummy (dos DELIVERY activas, una DINE_IN activa, una COMPLETED)
    OrderPreview orders[CAPACITY] = {
        {101, "DELIVERY", "PENDING", "A ", 1},     // Activa DELIVERY (1)
        {102, "DINE_IN", "IN_PROGRESS", "B ", 2},  // Activa DINE_IN 
        {103, "DELIVERY", "IN_PROGRESS", "C ", 1}, // Activa DELIVERY (2)
        {104, "DELIVERY", "COMPLETED", "D ", 3}    // Completada 
    };

    // Arreglo de punteros para la vista y su cantidad lógica
    OrderPreview *view[CAPACITY];
    int viewCount = 0;

    // E4: Muestra los estados de 'orders' antes de construir la vista
    cout << "=========================================" << endl;
    cout << " E4: Estado de 'orders' ANTES de la vista" << endl;
    cout << "=========================================" << endl;
    displayOrders(orders, CAPACITY, "Original collection:");

    // E2: Filtrar y copiar únicamente las direcciones de órdenes activas de tipo DELIVERY
    // Una orden activa es PENDING o IN_PROGRESS.
    for (int i = 0; i < CAPACITY; i++)
    {
        if (orders[i].orderType == "DELIVERY" && 
            (orders[i].status == "PENDING" || orders[i].status == "IN_PROGRESS"))
        {
            view[viewCount] = &orders[i]; // Guardamos el puntero prestado
            viewCount++;
        }
    }

    // E3: Muestra los IDs que quedaron en la vista
    cout << "\n=========================================" << endl;
    cout << " E3: IDs en la vista (DELIVERY activas)" << endl;
    cout << "=========================================" << endl;
    displayView(view, viewCount, "Vista filtrada:");

    // E4: Muestra los estados de 'orders' después de construir la vista
    cout << "\n=========================================" << endl;
    cout << " E4: Estado de 'orders' DESPUES de la vista" << endl;
    cout << "=========================================" << endl;
    displayOrders(orders, CAPACITY, "Original collection (intact):");

    return 0;
}

// Función para mostrar las órdenes originales
void displayOrders(const OrderPreview orders[], int count, const string& title)
{
    cout << title << endl;
    for (int index = 0; index < count; index++)
    {
        cout << "  - ID: " << orders[index].orderId
             << " | Tipo: " << orders[index].orderType
             << " | Estado: " << orders[index].status
             << " | Edificio: " << orders[index].building
             << " | Prioridad: " << orders[index].priority << endl;
    }
}

// Función para mostrar la vista basada en punteros
void displayView(OrderPreview *view[], int count, const string& title)
{
    cout << title << endl;
    for (int index = 0; index < count; index++)
    {
        cout << "  - ID en Vista: " << view[index]->orderId
             << " | Tipo: " << view[index]->orderType
             << " | Estado: " << view[index]->status << endl;
    }
}