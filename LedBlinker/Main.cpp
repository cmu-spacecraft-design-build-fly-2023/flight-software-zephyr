// ======================================================================
// \title  Main.cpp
// \brief main program for the F' application. Intended for CLI-based systems (Linux, macOS)
//
// ======================================================================
// Used to access topology functions
#include <LedBlinker/Top/LedBlinkerTopologyAc.hpp>
#include <LedBlinker/Top/LedBlinkerTopology.hpp>

// Used for logging
#include <Os/Log.hpp>

// Instantiate a system logger that will handle Fw::Logger::logMsg calls
Os::Log logger;

#define CONSOLE_DEVICE DEVICE_DT_GET(DT_CHOSEN(zephyr_console))
#define USB_CDC_ACM_CHECK DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart)
const struct device *serial = CONSOLE_DEVICE;

// const struct device *serial = DEVICE_DT_GET(DT_NODELABEL(cdc_acm_uart0));

int main()
{
    // Wait for a serial connection to be established
    uint32_t dtr = 0;
	while (!dtr) {
     	uart_line_ctrl_get(serial, UART_LINE_CTRL_DTR, &dtr);
	 	k_sleep(K_MSEC(100));
	}

    Fw::Logger::logMsg("Hello from FPrime/Zephyr/PyCubed\n");

    // Object for communicating state to the reference topology
    LedBlinker::TopologyState inputs;
    inputs.dev = serial;
    inputs.uartBaud = 115200;

    // Setup topology
    Fw::Logger::logMsg("Setting up topology...\n");
    LedBlinker::setupTopology(inputs);
    Fw::Logger::logMsg("Topology set\n");

    while(true)
    {
        Fw::Logger::logMsg("Looping");
        rateDriver.cycle();
        k_usleep(1);
    }

    return 0;
}
