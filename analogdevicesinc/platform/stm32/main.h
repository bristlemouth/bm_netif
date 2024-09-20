#include <stdint.h>

#define     __IO    volatile             /*!< Defines 'read / write' permissions */

typedef enum
{
/* =======================================  ARM Cortex-M33 Specific Interrupt Numbers  ======================================= */
  Reset_IRQn                = -15,    /*!< -15 Reset Vector, invoked on Power up and warm reset              */
  NonMaskableInt_IRQn       = -14,    /*!< -14 Non maskable Interrupt, cannot be stopped or preempted        */
  HardFault_IRQn            = -13,    /*!< -13 Hard Fault, all classes of Fault                              */
  MemoryManagement_IRQn     = -12,    /*!< -12 Memory Management, MPU mismatch, including Access Violation
                                               and No Match                                                  */
  BusFault_IRQn             = -11,    /*!< -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                               related Fault                                                 */
  UsageFault_IRQn           = -10,    /*!< -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition */
  SecureFault_IRQn          =  -9,    /*!< -9  Secure Fault                                                  */
  SVCall_IRQn               =  -5,    /*!< -5  System Service Call via SVC instruction                       */
  DebugMonitor_IRQn         =  -4,    /*!< -4  Debug Monitor                                                 */
  PendSV_IRQn               =  -2,    /*!< -2  Pendable request for system service                           */
  SysTick_IRQn              =  -1,    /*!< -1  System Tick Timer                                             */

/* ===========================================  STM32U575xx Specific Interrupt Numbers  ================================= */
  WWDG_IRQn                 = 0,      /*!< Window WatchDog interrupt                                         */
  PVD_PVM_IRQn              = 1,      /*!< PVD/PVM through EXTI Line detection Interrupt                     */
  RTC_IRQn                  = 2,      /*!< RTC non-secure interrupt                                          */
  RTC_S_IRQn                = 3,      /*!< RTC secure interrupt                                              */
  TAMP_IRQn                 = 4,      /*!< Tamper non-secure interrupt                                       */
  RAMCFG_IRQn               = 5,      /*!< RAMCFG global interrupt                                           */
  FLASH_IRQn                = 6,      /*!< FLASH non-secure global interrupt                                 */
  FLASH_S_IRQn              = 7,      /*!< FLASH secure global interrupt                                     */
  GTZC_IRQn                 = 8,      /*!< Global TrustZone Controller interrupt                             */
  RCC_IRQn                  = 9,      /*!< RCC non secure global interrupt                                   */
  RCC_S_IRQn                = 10,     /*!< RCC secure global interrupt                                       */
  EXTI0_IRQn                = 11,     /*!< EXTI Line0 interrupt                                              */
  EXTI1_IRQn                = 12,     /*!< EXTI Line1 interrupt                                              */
  EXTI2_IRQn                = 13,     /*!< EXTI Line2 interrupt                                              */
  EXTI3_IRQn                = 14,     /*!< EXTI Line3 interrupt                                              */
  EXTI4_IRQn                = 15,     /*!< EXTI Line4 interrupt                                              */
  EXTI5_IRQn                = 16,     /*!< EXTI Line5 interrupt                                              */
  EXTI6_IRQn                = 17,     /*!< EXTI Line6 interrupt                                              */
  EXTI7_IRQn                = 18,     /*!< EXTI Line7 interrupt                                              */
  EXTI8_IRQn                = 19,     /*!< EXTI Line8 interrupt                                              */
  EXTI9_IRQn                = 20,     /*!< EXTI Line9 interrupt                                              */
  EXTI10_IRQn               = 21,     /*!< EXTI Line10 interrupt                                             */
  EXTI11_IRQn               = 22,     /*!< EXTI Line11 interrupt                                             */
  EXTI12_IRQn               = 23,     /*!< EXTI Line12 interrupt                                             */
  EXTI13_IRQn               = 24,     /*!< EXTI Line13 interrupt                                             */
  EXTI14_IRQn               = 25,     /*!< EXTI Line14 interrupt                                             */
  EXTI15_IRQn               = 26,     /*!< EXTI Line15 interrupt                                             */
  IWDG_IRQn                 = 27,     /*!< IWDG global interrupt                                             */
  GPDMA1_Channel0_IRQn      = 29,     /*!< GPDMA1 Channel 0 global interrupt                                 */
  GPDMA1_Channel1_IRQn      = 30,     /*!< GPDMA1 Channel 1 global interrupt                                 */
  GPDMA1_Channel2_IRQn      = 31,     /*!< GPDMA1 Channel 2 global interrupt                                 */
  GPDMA1_Channel3_IRQn      = 32,     /*!< GPDMA1 Channel 3 global interrupt                                 */
  GPDMA1_Channel4_IRQn      = 33,     /*!< GPDMA1 Channel 4 global interrupt                                 */
  GPDMA1_Channel5_IRQn      = 34,     /*!< GPDMA1 Channel 5 global interrupt                                 */
  GPDMA1_Channel6_IRQn      = 35,     /*!< GPDMA1 Channel 6 global interrupt                                 */
  GPDMA1_Channel7_IRQn      = 36,     /*!< GPDMA1 Channel 7 global interrupt                                 */
  ADC1_IRQn                 = 37,     /*!< ADC1 global interrupt                                             */
  DAC1_IRQn                 = 38,     /*!< DAC1 global interrupt                                             */
  FDCAN1_IT0_IRQn           = 39,     /*!< FDCAN1 interrupt 0                                                */
  FDCAN1_IT1_IRQn           = 40,     /*!< FDCAN1 interrupt 1                                                */
  TIM1_BRK_IRQn             = 41,     /*!< TIM1 Break interrupt                                              */
  TIM1_UP_IRQn              = 42,     /*!< TIM1 Update interrupt                                             */
  TIM1_TRG_COM_IRQn         = 43,     /*!< TIM1 Trigger and Commutation interrupt                            */
  TIM1_CC_IRQn              = 44,     /*!< TIM1 Capture Compare interrupt                                    */
  TIM2_IRQn                 = 45,     /*!< TIM2 global interrupt                                             */
  TIM3_IRQn                 = 46,     /*!< TIM3 global interrupt                                             */
  TIM4_IRQn                 = 47,     /*!< TIM4 global interrupt                                             */
  TIM5_IRQn                 = 48,     /*!< TIM5 global interrupt                                             */
  TIM6_IRQn                 = 49,     /*!< TIM6 global interrupt                                             */
  TIM7_IRQn                 = 50,     /*!< TIM7 global interrupt                                             */
  TIM8_BRK_IRQn             = 51,     /*!< TIM8 Break interrupt                                              */
  TIM8_UP_IRQn              = 52,     /*!< TIM8 Update interrupt                                             */
  TIM8_TRG_COM_IRQn         = 53,     /*!< TIM8 Trigger and Commutation interrupt                            */
  TIM8_CC_IRQn              = 54,     /*!< TIM8 Capture Compare interrupt                                    */
  I2C1_EV_IRQn              = 55,     /*!< I2C1 Event interrupt                                              */
  I2C1_ER_IRQn              = 56,     /*!< I2C1 Error interrupt                                              */
  I2C2_EV_IRQn              = 57,     /*!< I2C2 Event interrupt                                              */
  I2C2_ER_IRQn              = 58,     /*!< I2C2 Error interrupt                                              */
  SPI1_IRQn                 = 59,     /*!< SPI1 global interrupt                                             */
  SPI2_IRQn                 = 60,     /*!< SPI2 global interrupt                                             */
  USART1_IRQn               = 61,     /*!< USART1 global interrupt                                           */
  USART2_IRQn               = 62,     /*!< USART2 global interrupt                                           */
  USART3_IRQn               = 63,     /*!< USART3 global interrupt                                           */
  UART4_IRQn                = 64,     /*!< UART4 global interrupt                                            */
  UART5_IRQn                = 65,     /*!< UART5 global interrupt                                            */
  LPUART1_IRQn              = 66,     /*!< LPUART1 global interrupt                                          */
  LPTIM1_IRQn               = 67,     /*!< LPTIM1 global interrupt                                           */
  LPTIM2_IRQn               = 68,     /*!< LPTIM2 global interrupt                                           */
  TIM15_IRQn                = 69,     /*!< TIM15 global interrupt                                            */
  TIM16_IRQn                = 70,     /*!< TIM16 global interrupt                                            */
  TIM17_IRQn                = 71,     /*!< TIM17 global interrupt                                            */
  COMP_IRQn                 = 72,     /*!< COMP1 and COMP2 through EXTI Lines interrupts                     */
  OTG_FS_IRQn               = 73,     /*!< USB OTG FS global interrupt                                       */
  CRS_IRQn                  = 74,     /*!< CRS global interrupt                                              */
  FMC_IRQn                  = 75,     /*!< FSMC global interrupt                                             */
  OCTOSPI1_IRQn             = 76,     /*!< OctoSPI1 global interrupt                                         */
  PWR_S3WU_IRQn             = 77,     /*!< PWR wake up from Stop3 interrupt                                  */
  SDMMC1_IRQn               = 78,     /*!< SDMMC1 global interrupt                                           */
  SDMMC2_IRQn               = 79,     /*!< SDMMC2 global interrupt                                           */
  GPDMA1_Channel8_IRQn      = 80,     /*!< GPDMA1 Channel 8 global interrupt                                 */
  GPDMA1_Channel9_IRQn      = 81,     /*!< GPDMA1 Channel 9 global interrupt                                 */
  GPDMA1_Channel10_IRQn     = 82,     /*!< GPDMA1 Channel 10 global interrupt                                */
  GPDMA1_Channel11_IRQn     = 83,     /*!< GPDMA1 Channel 11 global interrupt                                */
  GPDMA1_Channel12_IRQn     = 84,     /*!< GPDMA1 Channel 12 global interrupt                                */
  GPDMA1_Channel13_IRQn     = 85,     /*!< GPDMA1 Channel 13 global interrupt                                */
  GPDMA1_Channel14_IRQn     = 86,     /*!< GPDMA1 Channel 14 global interrupt                                */
  GPDMA1_Channel15_IRQn     = 87,     /*!< GPDMA1 Channel 15 global interrupt                                */
  I2C3_EV_IRQn              = 88,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQn              = 89,     /*!< I2C3 error interrupt                                              */
  SAI1_IRQn                 = 90,     /*!< Serial Audio Interface 1 global interrupt                         */
  SAI2_IRQn                 = 91,     /*!< Serial Audio Interface 2 global interrupt                         */
  TSC_IRQn                  = 92,     /*!< Touch Sense Controller global interrupt                           */
  RNG_IRQn                  = 94,     /*!< RNG global interrupt                                              */
  FPU_IRQn                  = 95,     /*!< FPU global interrupt                                              */
  HASH_IRQn                 = 96,     /*!< HASH global interrupt                                             */
  LPTIM3_IRQn               = 98,     /*!< LPTIM3 global interrupt                                           */
  SPI3_IRQn                 = 99,     /*!< SPI3 global interrupt                                             */
  I2C4_ER_IRQn              = 100,    /*!< I2C4 Error interrupt                                              */
  I2C4_EV_IRQn              = 101,    /*!< I2C4 Event interrupt                                              */
  MDF1_FLT0_IRQn            = 102,    /*!< MDF1 Filter 0 global interrupt                                    */
  MDF1_FLT1_IRQn            = 103,    /*!< MDF1 Filter 1 global interrupt                                    */
  MDF1_FLT2_IRQn            = 104,    /*!< MDF1 Filter 2 global interrupt                                    */
  MDF1_FLT3_IRQn            = 105,    /*!< MDF1 Filter 3 global interrupt                                    */
  UCPD1_IRQn                = 106,    /*!< UCPD1 global interrupt                                            */
  ICACHE_IRQn               = 107,    /*!< Instruction cache global interrupt                                */
  LPTIM4_IRQn               = 110,    /*!< LPTIM4 global interrupt                                           */
  DCACHE1_IRQn              = 111,    /*!< Data cache global interrupt                                       */
  ADF1_IRQn                 = 112,    /*!< ADF interrupt                                                     */
  ADC4_IRQn                 = 113,    /*!< ADC4 (12bits) global interrupt                                    */
  LPDMA1_Channel0_IRQn      = 114,    /*!< LPDMA1 SmartRun Channel 0 global interrupt                        */
  LPDMA1_Channel1_IRQn      = 115,    /*!< LPDMA1 SmartRun Channel 1 global interrupt                        */
  LPDMA1_Channel2_IRQn      = 116,    /*!< LPDMA1 SmartRun Channel 2 global interrupt                        */
  LPDMA1_Channel3_IRQn      = 117,    /*!< LPDMA1 SmartRun Channel 3 global interrupt                        */
  DMA2D_IRQn                = 118,    /*!< DMA2D global interrupt                                            */
  DCMI_PSSI_IRQn            = 119,    /*!< DCMI/PSSI global interrupt                                        */
  OCTOSPI2_IRQn             = 120,    /*!< OCTOSPI2 global interrupt                                         */
  MDF1_FLT4_IRQn            = 121,    /*!< MDF1 Filter 4 global interrupt                                    */
  MDF1_FLT5_IRQn            = 122,    /*!< MDF1 Filter 5 global interrupt                                    */
  CORDIC_IRQn               = 123,    /*!< CORDIC global interrupt                                           */
  FMAC_IRQn                 = 124,    /*!< FMAC global interrupt                                             */
} IRQn_Type;

typedef enum
{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED   = 0x01
} HAL_LockTypeDef;

typedef enum
{
  HAL_DMA_STATE_RESET   = 0x00U, /*!< DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY   = 0x01U, /*!< DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY    = 0x02U, /*!< DMA process is ongoing              */
  HAL_DMA_STATE_ERROR   = 0x03U, /*!< DMA error state                     */
  HAL_DMA_STATE_ABORT   = 0x04U, /*!< DMA Abort state                     */
  HAL_DMA_STATE_SUSPEND = 0x05U, /*!< DMA Suspend state                   */

} HAL_DMA_StateTypeDef;

typedef struct
{
  uint32_t Request;               /*!< Specifies the DMA channel request.
                                       This parameter can be a value of @ref DMA_Request_Selection                    */

  uint32_t BlkHWRequest;          /*!< Specifies the Block hardware request mode for DMA channel.
                                       Block Hardware request feature can be used only with dedicated peripherals.
                                       This parameter can be a value of @ref DMA_Block_Request                        */

  uint32_t Direction;             /*!< Specifies the transfer direction for DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Direction                   */

  uint32_t SrcInc;                /*!< Specifies the source increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Increment_Mode                */

  uint32_t DestInc;               /*!< Specifies the destination increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Increment_Mode           */

  uint32_t SrcDataWidth;          /*!< Specifies the source data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Data_Width                    */

  uint32_t DestDataWidth;         /*!< Specifies the destination data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Data_Width               */

  uint32_t Priority;              /*!< Specifies the priority level for the DMA channel.
                                       This parameter can be a value of @ref DMA_Priority_Level                       */

  uint32_t SrcBurstLength;        /*!< Specifies the source burst length (number of beats within a burst) for the DMA
                                       channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t DestBurstLength;       /*!< Specifies the destination burst length (number of beats within a burst) for the
                                       DMA channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t TransferAllocatedPort; /*!< Specifies the transfer allocated ports.
                                       This parameter can be a combination of @ref DMA_Transfer_Allocated_Port        */

  uint32_t TransferEventMode;     /*!< Specifies the transfer event mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Event_Mode                  */

  uint32_t Mode;                  /*!< Specifies the transfer mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Mode                        */

} DMA_InitTypeDef;

typedef struct
{
  uint32_t Priority;          /*!< Specifies the priority level for the DMA channel.
                                   This parameter can be a value of @ref DMA_Priority_Level        */
  uint32_t LinkStepMode;      /*!< Specifies the link step mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Step_Mode      */
  uint32_t LinkAllocatedPort; /*!< Specifies the linked-list allocated port for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Allocated_Port */
  uint32_t TransferEventMode; /*!< Specifies the transfer event mode for the DMA channel.
                                   This parameter can be a value of @ref DMA_Transfer_Event_Mode   */
  uint32_t LinkedListMode;    /*!< Specifies linked-list transfer mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_LinkedList_Mode     */
} DMA_InitLinkedListTypeDef;

typedef struct
{
  __IO uint32_t CLBAR;        /*!< DMA channel x linked-list base address register, Address offset: 0x50 + (x * 0x80) */
       uint32_t RESERVED1[2]; /*!< Reserved 1,                                      Address offset: 0x54 -- 0x58      */
  __IO uint32_t CFCR;         /*!< DMA channel x flag clear register,               Address offset: 0x5C + (x * 0x80) */
  __IO uint32_t CSR;          /*!< DMA channel x flag status register,              Address offset: 0x60 + (x * 0x80) */
  __IO uint32_t CCR;          /*!< DMA channel x control register,                  Address offset: 0x64 + (x * 0x80) */
       uint32_t RESERVED2[10];/*!< Reserved 2,                                      Address offset: 0x68 -- 0x8C      */
  __IO uint32_t CTR1;         /*!< DMA channel x transfer register 1,               Address offset: 0x90 + (x * 0x80) */
  __IO uint32_t CTR2;         /*!< DMA channel x transfer register 2,               Address offset: 0x94 + (x * 0x80) */
  __IO uint32_t CBR1;         /*!< DMA channel x block register 1,                  Address offset: 0x98 + (x * 0x80) */
  __IO uint32_t CSAR;         /*!< DMA channel x source address register,           Address offset: 0x9C + (x * 0x80) */
  __IO uint32_t CDAR;         /*!< DMA channel x destination address register,      Address offset: 0xA0 + (x * 0x80) */
  __IO uint32_t CTR3;         /*!< DMA channel x transfer register 3,               Address offset: 0xA4 + (x * 0x80) */
  __IO uint32_t CBR2;         /*!< DMA channel x block register 2,                  Address offset: 0xA8 + (x * 0x80) */
       uint32_t RESERVED3[8]; /*!< Reserved 3,                                      Address offset: 0xAC -- 0xC8      */
  __IO uint32_t CLLR;         /*!< DMA channel x linked-list address register,      Address offset: 0xCC + (x * 0x80) */
} DMA_Channel_TypeDef;

typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef       *Instance;                             /*!< Register the DMA channel base address   */
  DMA_InitTypeDef           Init;                                  /*!< DMA channel init parameters             */
  DMA_InitLinkedListTypeDef InitLinkedList;                        /*!< DMA channel linked-list init parameters */
  HAL_LockTypeDef           Lock;                                  /*!< DMA locking object                      */
  uint32_t                  Mode;                                  /*!< DMA transfer mode                       */
  __IO HAL_DMA_StateTypeDef State;                                 /*!< DMA transfer state                      */
  __IO uint32_t             ErrorCode;                             /*!< DMA error code                          */
  void                      *Parent;                               /*!< Parent object state                     */
  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);     /*!< DMA transfer complete callback          */
  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA half transfer complete callback     */
  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer error callback             */
  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer Abort callback             */
  void (* XferSuspendCallback)(struct __DMA_HandleTypeDef *hdma);  /*!< DMA transfer Suspend callback           */
  struct __DMA_QListTypeDef  *LinkedListQueue;                     /*!< DMA linked-list queue                   */
} DMA_HandleTypeDef;

void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
