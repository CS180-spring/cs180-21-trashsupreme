<script lang="ts">
import { defineComponent } from 'vue';
import type {Types} from '../../types'
import AddButton from '../General_Components/AddButton.vue';
import { input, dropdown } from '@/tailwindClasses';
    export default defineComponent ({
        data() {return {
            input, dropdown, 
            key: "",
            value: ""
        }},
        components: {
            AddButton
        },
        props: {
            options: Array<string>
        },
        emits:['submit'],
        methods: {
            submit() {
                this.$emit('submit', this.key, this.value);
            }
        },
        mounted() {
            if (this.options != null) {
                this.key = this.options[0]
            }
        }
    })
</script>

<template>
    <span>
        <select :class=dropdown v-model="key">
            <option v-for="option in options" :key="option">{{ option }}</option>
        </select>
        <input :class=input v-model="value" @keyup.enter="submit">
        <AddButton @click="submit"/>
    </span>
</template>

<style>

</style>