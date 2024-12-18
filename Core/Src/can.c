/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_7TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
	  /* CAN filter configuration */
	        CAN_FilterTypeDef canFilterConfig0;
	        canFilterConfig0.FilterActivation = ENABLE;//отключил - второй заработал

	        canFilterConfig0.FilterBank = 0;  // Use bank 0
	        canFilterConfig0.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	        canFilterConfig0.FilterIdHigh = 0x0000;
	        canFilterConfig0.FilterIdLow = 0x0000;
	        canFilterConfig0.FilterMaskIdHigh = 0x0000;
	        canFilterConfig0.FilterMaskIdLow = 0x0000;
	        canFilterConfig0.FilterMode = CAN_FILTERMODE_IDMASK;
	        canFilterConfig0.FilterScale = CAN_FILTERSCALE_32BIT;
	        if (HAL_CAN_ConfigFilter(&hcan1, &canFilterConfig0) != HAL_OK)
	      {
	          // Filter configuration Error
	          Error_Handler();
	      }

      /* Start the CAN peripheral */
      if (HAL_CAN_Start(&hcan1) != HAL_OK)
      {
          // Start Error
          Error_Handler();
      }

      /* Activate CAN notifications */
      if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY ) != HAL_OK)
      {
          // Notification Error
          Error_Handler();
      }

      /* Transmission */
      CAN_TxHeaderTypeDef TxHeader;
      uint32_t TxMailbox;
      uint8_t TxData[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};  // Example data

      TxHeader.DLC = 8;  // Data length
      TxHeader.IDE = CAN_ID_STD;  // Using standard identifier
      TxHeader.StdId = 0x423;  // Standard identifier of the message
      TxHeader.RTR = CAN_RTR_DATA;  // Message is a data frame

      if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
      {
          // Transmission request Error
          Error_Handler();
      }

      if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE ) != HAL_OK)
            {
                // Notification Error
                Error_Handler();
            }
  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 24;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_7TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = ENABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = ENABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */
  /* CAN filter configuration for CAN2 */



           /* CAN filter configuration for CAN2 */
               CAN_FilterTypeDef canFilterConfig2;
               canFilterConfig2.FilterActivation = ENABLE;
               canFilterConfig2.SlaveStartFilterBank = 14;  // Use bank 0
               canFilterConfig2.FilterBank = 14; // Use a different bank for CAN2
               canFilterConfig2.FilterFIFOAssignment = CAN_FILTER_FIFO1;
               canFilterConfig2.FilterIdHigh = 0x0000;
               canFilterConfig2.FilterIdLow = 0x0000;
               canFilterConfig2.FilterMaskIdHigh = 0x0000;
               canFilterConfig2.FilterMaskIdLow = 0x0000;
               canFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
               canFilterConfig2.FilterScale = CAN_FILTERSCALE_32BIT;
               if (HAL_CAN_ConfigFilter(&hcan2, &canFilterConfig2) != HAL_OK)
               {
                   // Filter configuration Error
                   Error_Handler();
               }

               /* Start the CAN peripheral */
               if (HAL_CAN_Start(&hcan2) != HAL_OK)
               {
                   // Start Error
                   Error_Handler();
               }

               /* Activate CAN notifications */
               if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
               {
                   // Notification Error
                   Error_Handler();
               }

               /* Transmission via CAN2 */
               CAN_TxHeaderTypeDef TxHeader;
               uint32_t TxMailbox;
               uint8_t TxData[8] = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10}; // Example data for CAN2

               TxHeader.DLC = 8; // Data length
               TxHeader.IDE = CAN_ID_STD; // Using standard identifier
               TxHeader.StdId = 0x524; // Standard identifier of the message for CAN2
               TxHeader.RTR = CAN_RTR_DATA; // Message is a data frame

               if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox) != HAL_OK)
               {
                   // Transmission request Error
                   Error_Handler();
               }
               if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING | CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE ) != HAL_OK)
                           {
                               // Notification Error
                               Error_Handler();
                           }
  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_SCE_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)//can1
{
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};  // Example data
    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    }


}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)//can2
{
    CAN_RxHeaderTypeDef RxHeader1;
    uint8_t RxData1[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};  // Example data
    if(HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &RxHeader1, RxData1) == HAL_OK)
    {
       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    }

}

/* USER CODE END 1 */
