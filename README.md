# 🏥 VR Medical LLM

**Breast Cancer Classification & Segmentation with VR Visualization**

An AI-powered medical diagnostic system that classifies and segments breast cancer in ultrasound images, with predictions visualized inside a 3D Unreal Engine hospital environment via Pixel Streaming.

Built with Vision Transformers, EfficientNet, UNETR, UNet, Flask, MERN stack, and Unreal Engine.

---

## 📌 Overview

- Classify ultrasound images as **Normal**, **Benign**, or **Malignant**
- Segment tumors using deep learning (UNETR / UNet)
- Stream annotated results into an immersive Unreal Engine hospital scene
- Supports both image and video input

## 🗂 Dataset

**BUSI (Breast Ultrasound Images)** — 780+ images from 600 patients (PNG, ~500×500).

Augmentation: horizontal/vertical flip, random rotation (±20°), class balancing.

## 🏗 Architecture

```
React Frontend → Node.js Backend → Flask AI Server → Unreal Engine (WebSocket) → Pixel Streaming → Browser
```

## 🧪 Models

| Model | Task | Key Metric |
|-------|------|------------|
| **ViT_B_16** | Classification | Test Acc: 63.94% |
| **EfficientNet-B0** | Classification | Test Acc: 92.23% |
| **UNETR** | Segmentation | Acc: 95.62% |
| **UNet** | Segmentation | Test Acc: 77.55% |

## 🖥️ Tech Stack

| Layer | Technologies |
|-------|-------------|
| AI/ML | Python, PyTorch, TensorFlow, OpenCV, ViT, EfficientNet, UNETR, UNet |
| Backend | Flask (inference), Node.js, Express |
| Frontend | React, Tailwind CSS |
| Auth & DB | MongoDB Atlas, JWT, Bcrypt, Nodemailer, Twilio (OTP) |
| VR | Unreal Engine (C++), WebSockets, Pixel Streaming |

## 🎮 Unreal Engine Integration

The UE environment displays input images, predicted outputs, segmentation masks, and ground truth side-by-side inside a virtual hospital. Uses WebSocket for communication and runtime Base64 texture decoding.

## 🚀 Key Features

- Multi-model selection (classification + segmentation)
- Image & video support (frame-by-frame inference via OpenCV)
- Real-time VR visualization with Pixel Streaming
- Secure auth (email verification, OTP-based 2FA, JWT)

## 🎯 Use Cases

- Medical student training
- Oncologist diagnostic assistance
- AI-assisted radiology research

## 📈 Future Work

- Improve ViT generalization with more data
- 3D volumetric segmentation
- Cloud GPU deployment
- Integrate medical LLM for automated reports
- Explainability (Grad-CAM, attention maps)