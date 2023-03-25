import { configureStore } from '@reduxjs/toolkit';
import frameSlice from './features/frame/state/frameSlice';

export const store = configureStore({
  reducer: {
    frame: frameSlice,
  },
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;
